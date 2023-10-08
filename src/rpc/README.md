# Skynet RPC

The RPC server allows clients to interact with the Skynet network. It is a JSON-RPC server that exposes a set of methods that can be called by clients.

It's through this interface that the Skynet Core GUI interacts with the node and performs actions such as sending transactions, fetching blocks, etc.

## Methods

The RPC server exposes the following methods:

### `get_block`

Fetches a block by its hash.

#### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| `hash` | `string` | The hash of the block to fetch. |

#### Returns

| Name | Type | Description |
| ---- | ---- | ----------- |
| `block` | `object` | The block. |

### `get_block_by_height`

Fetches a block by its height in the chain.

#### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| `height` | `number` | The height of the block to fetch. |

#### Returns

| Name | Type | Description |
| ---- | ---- | ----------- |
| `block` | `object` | The block. |

### `get_blocks`

Fetches a range of blocks.

#### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| `from` | `number` | The height of the first block to fetch. |

#### Returns

| Name | Type | Description |
| ---- | ---- | ----------- |
| `blocks` | `array` | The blocks. |

### `get_transactions`

Fetches the transactions waiting to be included in the next block (transactions inside the transaction pool).

#### Parameters

None.

#### Returns

| Name | Type | Description |
| ---- | ---- | ----------- |
| `transactions` | `array` | The transactions. |



