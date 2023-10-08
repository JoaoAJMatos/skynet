/**
 * @file   json_rpc.hpp
 * @author JoaoAJMatos
 *
 * @brief Single header JSON-RPC 2.0 framework
 *        for C++11 and above.
 * 
 *        This header implements the JSON-RPC 2.0 specification
 *        as described in https://www.jsonrpc.org/specification.
 * 
 *        This header is based on the work of:
 *        - Peter Spiess-Knafl (https://www.github.com/cinemast) | https://www.github.com/jsonrpcx/json-rpc-cxx
 * 
 *        This header is part of the Skynet project (https://www.github.com/JoaoAJMatos/skynet) 
 *        and is distributed under the MIT License.
 * 
 *        Features:
 *        - JSON-RPC 2.0 specification compliant (client and server)
 *        - Transport agnostic interfaces
 *        - Compile-time mapping (using nlohmann's arbitrary type conversion)
 *        - Runtime type checking  
 *        - Cross-platform	    
 *
 * @version 0.1
 * @date 2023-10-05
 * @license MIT
 * @copyright Copyright (c) 2023
 */

#ifndef SKYNET_RPC_SERVER_HPP
#define SKYNET_RPC_SERVER_HPP

/** C++ Includes */
#include <functional>
#include <limits>
#include <utility>
#include <vector>
#include <exception>
#include <string>
#include <variant>

/** Skynet Includes */
#include <json/json.hpp> // nlohmann/json.hpp

/** MACROS */
#if defined(__APPLE__)
#define inline __attribute__((always_inline)) /** The inline keyword seems to cause problems on some Macs */
#endif // __APPLE__


namespace rpc
{
    using nlohmann::json;

    typedef std::function<json(const json&)> MethodHandle;
    typedef std::function<void(const std::string&)> NotificationHandle;
    typedef std::vector<json> positional_parameter;
    typedef std::map<std::string, json> named_parameter;
    typedef std::variant<int, std::string> id_type;

    typedef std::vector<std::string> NamedParamMapping;
    static NamedParamMapping NAMED_PARAM_MAPPING;

    enum class version { 
        v1, 
        v2 
    };

    enum error_type {
        PARSE_ERROR      = -32700,
        INVALID_REQUEST  = -32600,
        METHOD_NOT_FOUND = -32601,
        INVALID_PARAMS   = -32602,
        INTERNAL_ERROR   = -32603,
        SERVER_ERROR,
        INVALID
    };

    struct JsonRpcResponse {
        id_type id;
        json result;
    };

    /** HELPER FUNCTIONS */
    static inline bool has_key(const json& j, const std::string& key) { return j.find(key) != j.end(); }
    static inline bool has_key_type(const json& j, const std::string& key, json::value_t type) { return has_key(j, key) && j[key].type() == type; }
    
    static inline bool valid_id(const json& request) {
        return has_key(request, "id") && (request["id"].is_number() || request["id"].is_string() || request["id"].is_null());
    }

    static inline bool valid_id_not_null(const json& request) {
        return has_key(request, "id") && (request["id"].is_number() || request["id"].is_string());
    }


    /**
     * @brief The base class for all JSON-RPC 2.0 exceptions.
     */
    class JsonRpcException : public std::exception 
    {
    public:
        JsonRpcException(int code, const std::string& message) noexcept
            : code(code), message(message), data(nullptr), err(std::to_string(code) + ": " + message) {}
        JsonRpcException(int code, const std::string& message, const json& data) noexcept
            : code(code), message(message), data(data), err(std::to_string(code) + ": " + message) {}

        error_type Type() const {
            if (code >= -32603 && code <= -32600) return static_cast<error_type>(code);
            if (code >= -32099 && code <= -32000) return error_type::SERVER_ERROR;
            if (code == -32700) return error_type::PARSE_ERROR;
            return error_type::INVALID;
        }

        int Code() const noexcept { return code; }
        const std::string& Message() const noexcept { return message; }
        const json& Data() const noexcept { return data; }

        const char* what() const noexcept override { return err.c_str(); }

        static inline JsonRpcException fromJson(const json &value) {
            bool has_code = has_key_type(value, "code", json::value_t::number_integer);
            bool has_message = has_key_type(value, "message", json::value_t::string);
            bool has_data = has_key(value, "data");
            if (has_code && has_message) {
                if (has_data) {
                    return JsonRpcException(value["code"], value["message"], value["data"]);
                }
                return JsonRpcException(value["code"], value["message"]);
            }
            return JsonRpcException(error_type::INTERNAL_ERROR, R"(invalid error response: "code" (negative number) and "message" (string) are required)");
        }
    private:
        int code;
        std::string message;
        json data;
        std::string err;
    };

    /** Workaround due to forbidden partial template function specialization */
    template <typename T>
    struct type {};

    template <typename T>
    constexpr json::value_t GetType(type<std::vector<T>>) {
        return json::value_t::array;
    }

    template <typename T>
    constexpr json::value_t GetType(type<T>) {
        if (std::is_enum<T>::value) {
            return json::value_t::string;
        }
        return json::value_t::object;
    }

    constexpr json::value_t GetType(type<int>) { return json::value_t::number_integer; }
    constexpr json::value_t GetType(type<unsigned int>) { return json::value_t::number_unsigned; }
    constexpr json::value_t GetType(type<long>) { return json::value_t::number_integer; }
    constexpr json::value_t GetType(type<unsigned long>) { return json::value_t::number_unsigned; }
    constexpr json::value_t GetType(type<long long>) { return json::value_t::number_integer; }
    constexpr json::value_t GetType(type<unsigned long long>) { return json::value_t::number_unsigned; }
    constexpr json::value_t GetType(type<float>) { return json::value_t::number_float; }
    constexpr json::value_t GetType(type<double>) { return json::value_t::number_float; }
    constexpr json::value_t GetType(type<bool>) { return json::value_t::boolean; }
    constexpr json::value_t GetType(type<std::string>) { return json::value_t::string; }
    constexpr json::value_t GetType(type<short>) { return json::value_t::number_integer; }
    constexpr json::value_t GetType(type<unsigned short>) { return json::value_t::number_unsigned; }

    /**
     * @brief Returns the JSON type name of the given type.
     * @param type The type to get the name of.
     * @return The JSON type name of the given type.
     */
    inline std::string type_name(json::value_t type) {
        switch (type) {
            case json::value_t::object:
                return "object";
            case json::value_t::array:
                return "array";
            case json::value_t::string:
                return "string";
            case json::value_t::boolean:
                return "boolean";
            case json::value_t::number_integer:
                return "integer";
            case json::value_t::number_unsigned:
                return "unsigned integer";
            case json::value_t::number_float:
                return "float";
            default:
                return "null";
        }
    }

    template <typename T>
    inline void check_param_type(size_t index, const json& x, json::value_t expectedType, typename std::enable_if<std::is_arithmetic<T>::value>::type * = 0) {
        if (expectedType == json::value_t::number_unsigned && x.type() == json::value_t::number_integer) {
            if (x.get<long long int>() < 0)
                throw JsonRpcException(error_type::INVALID_PARAMS, "invalid parameter: must be " + type_name(expectedType) + ", got " + type_name(x.type()), index);
        }
        else if (x.type() == json::value_t::number_unsigned && expectedType == json::value_t::number_integer) {
            if (x.get<unsigned long long int>() > std::numeric_limits<long long int>::max())
                throw JsonRpcException(error_type::INVALID_PARAMS, "invalid parameter: exceeds value range of " + type_name(expectedType), index);
        }
        else if ((x.type() == json::value_t::number_unsigned || x.type() == json::value_t::number_integer) && expectedType == json::value_t::number_float) {
            if (x.get<long double>() > std::numeric_limits<double>::max())
                throw JsonRpcException(error_type::INVALID_PARAMS, "invalid parameter: exceeds value range of " + type_name(expectedType), index);
        }
        else if (x.type() != expectedType) {
            throw JsonRpcException(error_type::INVALID_PARAMS, "invalid parameter: must be " + type_name(expectedType) + ", got " + type_name(x.type()), index);
        }
    }

    template <typename T>
    inline void check_param_type(size_t index, const json& x, json::value_t expectedType, typename std::enable_if<!std::is_arithmetic<T>::value>::type * = 0) {
        if (x.type() != expectedType) {
            throw JsonRpcException(error_type::INVALID_PARAMS, "invalid parameter: must be " + type_name(expectedType) + ", got " + type_name(x.type()), index);
        }
    }

    //
    // HANDLE MAPPING
    //

    /**
     * @brief Creates a method handle for the given method.
     * @param method The method to create the handle for.
     * @return The method handle.
     */
    template <typename ReturnType, typename... ParamTypes, std::size_t... index>
    MethodHandle createMethodHandle(std::function<ReturnType(ParamTypes...)> method, std::index_sequence<index...>) {
        MethodHandle handle = [method](const json& params) -> json {
            size_t actualSize = params.size();
            size_t formalSize = sizeof...(ParamTypes);
            // TODO: Add lenient mode for backward compatible additional parameters
            if (actualSize != formalSize) {
                throw JsonRpcException(error_type::INVALID_PARAMS, "invalid number of parameters: expected " 
                                                                    + std::to_string(formalSize) + ", got " + std::to_string(actualSize));
            }
            (check_param_type<typename std::decay<ParamTypes>::type>(index, params[index], GetType(type<typename std::decay<ParamTypes>::type>())), ...);
            return method(params[index].get<typename std::decay<ParamTypes>::type>()...);
        };
        return handle;
    }

    template <typename ReturnType, typename... ParamTypes>
    MethodHandle methodHandle(std::function<ReturnType(ParamTypes...)> method) {
        return createMethodHandle(method, std::index_sequence_for<ParamTypes...>{});
    }

    template <typename ReturnType, typename... ParamTypes>
    MethodHandle GetHandle(std::function<ReturnType(ParamTypes...)> f) {
        return methodHandle(f);
    }

    /** Mapping for C-style function pointers */
    template <typename ReturnType, typename... ParamTypes>
    MethodHandle GetHandle(ReturnType (*f)(ParamTypes...)) {
        return GetHandle(std::function<ReturnType(ParamTypes...)>(f));
    }

    inline MethodHandle GetUncheckedHandle(std::function<json(const json&)> f) {
        MethodHandle handle = [f](const json& params) -> json {
            return f(params);
        };
        return handle;
    }

    //
    // NOTIFICATION MAPPING
    //

    /**
     * @brief Creates a notification handle for the given method.
     * @param method The method to create the handle for.
     * @return The notification handle.
     */
    template <typename... ParamTypes, std::size_t... index>
    NotificationHandle createNotificationHandle(std::function<void(ParamTypes...)> method, std::index_sequence<index...>) {
        NotificationHandle handle = [method](const json& params) {
            size_t actualSize = params.size();
            size_t formalSize = sizeof...(ParamTypes);
            // TODO: add lenient mode for backward compatible additional parameters
            if (actualSize != formalSize) {
                throw JsonRpcException(error_type::INVALID_PARAMS, "invalid number of parameters: expected " 
                                                                    + std::to_string(formalSize) + ", got " + std::to_string(actualSize));
            }
            (check_param_type<typename std::decay<ParamTypes>::type>(index, params[index], GetType(type<typename std::decay<ParamTypes>::type>())), ...);
            method(params[index].get<typename std::decay<ParamTypes>::type>()...);
        };
        return handle;
    }

    template <typename... ParamTypes>
    NotificationHandle notificationHandle(std::function<void(ParamTypes...)> method) {
        return createNotificationHandle(method, std::index_sequence_for<ParamTypes...>{});
    }

    template <typename... ParamTypes>
    NotificationHandle GetHandle(std::function<void(ParamTypes...)> f) {
        return notificationHandle(f);
    }

    /** Mapping for C-style function pointers */
    template <typename... ParamTypes>
    NotificationHandle GetHandle(void (*f)(ParamTypes...)) {
        return GetHandle(std::function<void(ParamTypes...)>(f));
    }

    inline NotificationHandle GetUncheckedHandle(std::function<void(const std::string&)> f) {
        NotificationHandle handle = [f](const std::string& params) {
            f(params);
        };
        return handle;
    }

    template <typename T, typename ReturnType, typename... ParamTypes>
    MethodHandle methodHandle(ReturnType (T::*method)(ParamTypes...), T& instance) {
        std::function<ReturnType(ParamTypes...)> function = [&instance, method](ParamTypes &&... params) -> ReturnType {
            return (instance.*method)(std::forward<ParamTypes>(params)...);
        };
        return methodHandle(function);
    }

    template <typename T, typename... ParamTypes>
    NotificationHandle notificationHandle(void (T::*method)(ParamTypes...), T& instance) {
        std::function<void(ParamTypes...)> function = [&instance, method](ParamTypes &&... params) -> void {
            return (instance.*method)(std::forward<ParamTypes>(params)...);
        };
        return notificationHandle(function);
    }

    template <typename T, typename ReturnType, typename... ParamTypes>
    MethodHandle GetHandle(ReturnType (T::*method)(ParamTypes...), T& instance) {
        std::function<ReturnType(ParamTypes...)> function = [&instance, method](ParamTypes &&... params) -> ReturnType {
            return (instance.*method)(std::forward<ParamTypes>(params)...);
        };
        return GetHandle(function);
    }

    template <typename T, typename... ParamTypes>
    NotificationHandle GetHandle(void (T::*method)(ParamTypes...), T& instance) {
        std::function<void(ParamTypes...)> function = [&instance, method](ParamTypes &&... params) -> void {
            return (instance.*method)(std::forward<ParamTypes>(params)...);
        };
        return GetHandle(function);
    }

    //
    // DISPATCHER
    //

    class Dispatcher 
    {
    public:
        Dispatcher() : methods(), notifications(), mapping() {}

        /**
         * @brief Adds a method to the dispatcher.
         * @param name The name of the method.
         * @param handle The method handle.
         * @param mapping The named parameter mapping.
         */
        bool Add(const std::string& name, MethodHandle callback, const NamedParamMapping& mapping = NAMED_PARAM_MAPPING) {
            if (contains(name)) return false;
            methods[name] = std::move(callback);
            if (!mapping.empty()) this->mapping[name] = mapping;
            return true;
        }

        /**
         * @brief Adds a notification to the dispatcher.
         * @param name The name of the notification.
         * @param handle The notification handle.
         * @param mapping The named parameter mapping.
         */
        bool Add(const std::string& name, NotificationHandle callback, const NamedParamMapping& mapping = NAMED_PARAM_MAPPING) {
            if (contains(name)) return false;
            notifications[name] = std::move(callback);
            if (!mapping.empty()) this->mapping[name] = mapping;
            return true;
        }

        JsonRpcException process_type_error(const std::string& name, JsonRpcException& e) {
            if (e.Code() == -32602 && !e.Data().empty()) {
                std::string message = e.Message() + " for parameter ";
                if (this->mapping.find(name) != this->mapping.end()) {
                    message += "\"" + mapping[name][e.Data().get<unsigned int>()] + "\"";
                }
                else {
                    message += std::to_string(e.Data().get<unsigned int>());
                }
                return JsonRpcException(e.Code(), message);
            }
            return e;
        }

        json InvokeMethod(const std::string& name, const json& params) {
            auto method = methods.find(name);
            if (method == methods.end()) {
                throw JsonRpcException(error_type::METHOD_NOT_FOUND, "method not found: " + name);
            }

            try {
                return method->second(normalize_parameter(name, params));
            }
            catch (json::type_error& e) {
                throw JsonRpcException(error_type::INVALID_PARAMS, "invalid parameter: " + std::string(e.what()));
            }
            catch (JsonRpcException& e) {
                throw process_type_error(name, e);
            }
        }

        void InvokeNotification(const std::string& name, const json& params) {
            auto notification = notifications.find(name);
            if (notification == notifications.end()) {
                throw JsonRpcException(error_type::METHOD_NOT_FOUND, "method not found: " + name);
            }

            try {
                notification->second(normalize_parameter(name, params));
            }
            catch (json::type_error& e) {
                throw JsonRpcException(error_type::INVALID_PARAMS, "invalid parameter: " + std::string(e.what()));
            }
            catch (JsonRpcException& e) {
                throw process_type_error(name, e);
            }
        }
    private:
        std::map<std::string, MethodHandle> methods;
        std::map<std::string, NotificationHandle> notifications;
        std::map<std::string, NamedParamMapping> mapping;

        inline bool contains(const std::string& name) const {
            return methods.find(name) != methods.end() || notifications.find(name) != notifications.end();
        }

        inline json normalize_parameter(const std::string& name, const json& params) {
            if (params.type() == json::value_t::array) return params;
            if (params.type() == json::value_t::object) {
                if (mapping.find(name) == mapping.end()) throw JsonRpcException(error_type::INVALID_PARAMS, "invalid parameter: named parameters are not supported");

                json result;
                for (auto const& p : mapping[name]) {
                    if (params.find(p) == params.end()) throw JsonRpcException(error_type::INVALID_PARAMS, "invalid parameter: missing parameter " + p);
                    result.push_back(params[p]);
                }
                return result;
            }
            throw JsonRpcException(error_type::INVALID_PARAMS, "invalid parameter: must be array or object");
        }
    };

    //
    // CLIENT CONNECTOR INTERFACE
    //

    class IClientConnector
    {
    public:
        virtual ~IClientConnector() = default;
        virtual std::string Send(const std::string& request) = 0;
    };

    //
    // RPC CLIENT
    //

    class JsonRpcClient 
    {
    public:
        JsonRpcClient(IClientConnector& connector, version v) : connector(connector), v(v) {}
        virtual ~JsonRpcClient() = default;

        template <typename T>
        T CallMethod(const id_type& id, const std::string& name) {
            return call_method(id, name, json::object()).result.get<T>();
        }

        template <typename T>
        T CallMethod(const id_type& id, const std::string& name, const positional_parameter& params) {
            return call_method(id, name, params).result.get<T>();
        }

        template <typename T>
        T CallMethodNamed(const id_type& id, const std::string& name, const named_parameter& params = {}) {
            return call_method(id, name, params).result.get<T>();
        }

        void CallNotification(const std::string& name, const positional_parameter& params = {}) {
            call_notification(name, params);
        }

        void CallNotificationNamed(const std::string& name, const named_parameter& params = {}) {
            call_notification(name, params);
        }

    protected:
        IClientConnector& connector;

    private:
        version v;

        JsonRpcResponse call_method(const id_type& id, const std::string& name, const json& params) {
            json request = {
                { "method", name },
                { "version", v == version::v1 ? "1.0" : "2.0" }
            };

            if (std::get_if<int>(&id) != nullptr) request["id"] = std::get<int>(id);
            else request["id"] = std::get<std::string>(id);

            if (!params.empty() && !params.is_null()) request["params"] = params;
            else if (params.is_array()) request["params"] = params;
            else if (v == version::v1) request["params"] = nullptr;

            try {
                json response = json::parse(connector.Send(request.dump()));
                if (has_key_type(response, "error", json::value_t::object)) throw JsonRpcException::fromJson(response["error"]);
                else if (has_key_type(response, "error", json::value_t::string)) throw JsonRpcException(error_type::INTERNAL_ERROR, response["error"]);

                if (has_key(response, "result") && has_key(response, "id")) {
                    if (response["id"].type() == json::value_t::string) return JsonRpcResponse{response["id"].get<std::string>(), response["result"].get<json>()};
                    else return JsonRpcResponse{response["id"].get<int>(), response["result"].get<json>()};
                }

                throw JsonRpcException(error_type::INTERNAL_ERROR, R"(invalid server response: neither "result" not "error" fields found)");
            } catch (json::parse_error& e) {
                throw JsonRpcException(error_type::PARSE_ERROR, "invalid JSON response from server: " + std::string(e.what()));
            }
        }

        void call_notification(const std::string& name, const json& params) {
            json request = {
                { "method", name }
            };

            if (v == version::v2) request["jsonrpc"] = "2.0";
            else request["id"] = nullptr;

            if (!params.empty() && !params.is_null()) request["params"] = params;
            else if (v == version::v1) request["params"] = nullptr;

            connector.Send(request.dump());
        }
    };

    //
    // BATCH CLIENT
    //

    class BatchRequest
    {
    public:
        BatchRequest() : call(json::array()) {}

        BatchRequest& AddMethodCall(const id_type& id, const std::string& name, const positional_parameter& params = {}) {
            json request = {
                { "method", name },
                { "params", params },
                { "jsonrpc", "2.0" }
            };

            if (std::get_if<int>(&id) != nullptr) request["id"] = std::get<int>(id);
            else request["id"] = std::get<std::string>(id);

            call.push_back(request);
            return *this;
        }

        BatchRequest& AddNamedMethodCall(const id_type& id, const std::string& name, const named_parameter& params = {}) {
            json request = {
                { "method", name },
                { "params", params },
                { "jsonrpc", "2.0" }
            };

            if (std::get_if<int>(&id) != nullptr) request["id"] = std::get<int>(id);
            else request["id"] = std::get<std::string>(id);

            call.push_back(request);
            return *this;
        }

        BatchRequest& AddNotificationCall(const std::string& name, const positional_parameter& params = {}) {
            call.push_back({
                { "method", name },
                { "params", params },
                { "jsonrpc", "2.0" }
            });
            return *this;
        }

        BatchRequest& AddNamedNotificationCall(const std::string& name, const named_parameter& params = {}) {
            call.push_back({
                { "method", name },
                { "params", params },
                { "jsonrpc", "2.0" }
            });
            return *this;
        }

        const json& Build() const { return call; }

    private:
        json call;
    };


    class BatchResponse
    {
    public:
        explicit BatchResponse(json&& response) : response(response), results(), errors(), nullIds() {
            for (auto& [key, value] : response.items()) {
                if (value.is_object() && valid_id_not_null(value) && has_key(value, "result")) results[value["id"]] = std::stoi(key);
                else if (value.is_object() && valid_id_not_null(value) && has_key(value, "error")) errors[value["id"]] = std::stoi(key);
                else nullIds.push_back(std::stoi(key));
            }
        }

        template <typename T>
        T Get(const json& id) {
            if (results.find(id) != results.end()) {
                try {
                    return response[results[id]]["result"].get<T>();
                } catch (json::type_error& e) {
                    throw JsonRpcException(error_type::PARSE_ERROR, "invalid return type: " + std::string(e.what()));
                }
            } else if (errors.find(id) != errors.end()) {
                throw JsonRpcException::fromJson(response[errors[id]]["error"]);
            }
            throw JsonRpcException(error_type::PARSE_ERROR, "invalid response: no result or error found for id " + id.dump());
        }

        bool HasErrors() { return !errors.empty() || !nullIds.empty(); }
        const std::vector<size_t> GetInvalidIndexes() { return nullIds; }
        const json& GetResponse() { return response; }

    private:
        json response;
        std::map<json, size_t> results;
        std::map<json, size_t> errors;
        std::vector<size_t> nullIds;
    };


    class BatchClient : public JsonRpcClient
    {
    public:
        explicit BatchClient(IClientConnector& connector) : JsonRpcClient(connector, version::v2) {}

        BatchResponse BatchCall(const BatchRequest& request) {
            try {
                json response = json::parse(connector.Send(request.Build().dump()));
                if (!response.is_array()) throw JsonRpcException(error_type::INTERNAL_ERROR, "invalid server response: expected array");
                return BatchResponse(std::move(response));
            } catch (json::parse_error& e) {
                throw JsonRpcException(error_type::PARSE_ERROR, "invalid JSON response from server: " + std::string(e.what()));
            }
        }
    };

    //
    // RPC SERVER
    //

    class JsonRpcServer
    {
    public:
        JsonRpcServer() : dispatcher() {}
        virtual ~JsonRpcServer() = default;
        virtual std::string HandleRequest(const std::string& request) = 0;

        bool Add(const std::string& name, MethodHandle callback, const NamedParamMapping& mapping = NAMED_PARAM_MAPPING) {
            if (name.rfind("rpc.", 0) == 0) return false;
            return dispatcher.Add(name, callback, mapping);
        }

        bool Add(const std::string& name, NotificationHandle callback, const NamedParamMapping& mapping = NAMED_PARAM_MAPPING) {
            if (name.rfind("rpc.", 0) == 0) return false;
            return dispatcher.Add(name, callback, mapping);
        }
    
    protected:
        Dispatcher dispatcher;
    };

    class JsonRpc2Server : public JsonRpcServer
    {
    public:
        JsonRpc2Server() = default;
        ~JsonRpc2Server() override = default;

        std::string HandleRequest(const std::string& requestString) override {
            try {
                json request = json::parse(requestString);
                if (request.is_array()) {
                    json result = json::array();
                    for (auto& r : request) {
                        json res = this->HandleSignleRequest(r);
                        if (!res.is_null()) result.push_back(res);
                    }
                    return result.dump();
                }
                else if (request.is_object()) {
                    json res = this->HandleSignleRequest(request);
                    if (!res.is_null()) return res.dump();
                    else return "";
                }
                else {
                    return json{{"id", nullptr}, {"error", {{"code", error_type::INVALID_REQUEST}, {"message", "invalid request: must be array or object"}}}, {"jsonrpc", "2.0"}}.dump();
                }
            } catch (json::parse_error& e) {
                return json{{"id", nullptr}, {"error", {{"code", error_type::PARSE_ERROR}, {"message", "parse error: " + std::string(e.what())}}}, {"jsonrpc", "2.0"}}.dump();
            }
        }

    private:
        json HandleSignleRequest(json& request) {
            json id = nullptr;
            if (valid_id(request)) id = request["id"];

            try {
                return ProcessSingleRequest(request);
            } catch (JsonRpcException &e) {
                json error = {{"code", e.Code()}, {"message", e.Message()}};
                if (!e.Data().empty()) error["data"] = e.Data();
                return json{{"id", id}, {"error", error}, {"jsonrpc", "2.0"}};
            } catch (std::exception &e) {
                return json{{"id", id}, {"error", {{"code", error_type::INTERNAL_ERROR}, {"message", e.what()}}}, {"jsonrpc", "2.0"}};
            } catch (...) {
                return json{{"id", id}, {"error", {{"code", error_type::INTERNAL_ERROR}, {"message", "internal server error"}}}, {"jsonrpc", "2.0"}};
            }
        }

        json ProcessSingleRequest(json& request) {
            if (!has_key_type(request, "jsonrpc", json::value_t::string) || request["jsonrpc"] != "2.0") {
                throw JsonRpcException(error_type::INVALID_REQUEST, R"(invalid request: missing jsonrpc field set to "2.0")");
            }
            if (!has_key_type(request, "method", json::value_t::string)) {
                throw JsonRpcException(error_type::INVALID_REQUEST, "invalid request: method field must be a string");
            }
            if (has_key(request, "id") && !valid_id(request)) {
                throw JsonRpcException(error_type::INVALID_REQUEST, "invalid request: id field must be a string, number, or null");
            }
            if (has_key(request, "params") && !(request["params"].is_array() || request["params"].is_object() || request["params"].is_null())) {
                throw JsonRpcException(error_type::INVALID_REQUEST, "invalid request: params field must be an array, object, or null");
            }
            if (!has_key(request, "params") || has_key_type(request, "params", json::value_t::null)) {
                request["params"] = json::array();
            }
            if (!has_key(request, "id")) {
                try {
                    dispatcher.InvokeNotification(request["method"], request["params"]);
                    return json();
                } catch (std::exception& e) {
                    return json();
                }
            }
            else {
                return {{"jsonrpc", "2.0"}, {"id", request["id"]}, {"result", dispatcher.InvokeMethod(request["method"], request["params"])}};
            }
        }
    };

} // namespace rpc

#endif //SKYNET_RPC_SERVER_HPP

// MIT License
// 
// Copyright (c) 2023 João Matos
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.