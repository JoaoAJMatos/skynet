import os               # for os.name
import sys              # for sys.exit
import subprocess       # for subprocess.call
import shutil           # for shutil.copyfile
import time             # for time.sleep
import urllib.request   # for urllib.request.urlretrieve
import ctypes           # for ctypes.windll.shell32.IsUserAnAdmin

DEFAULT_INSTALL_DIR_POSIX   = '/usr/local/bin'
DEFAULT_INSTALL_DIR_WINDOWS = 'C:\\Program Files\\'
DOWNLOAD_URL_POSIX   = ''
DOWNLOAD_URL_WINDOWS = ''

def is_posix():
      return os.name == 'posix'

def die_if_not_admin():
      if is_posix():
            if os.geteuid() != 0:
                  raise Exception('ERROR: Must be run as root/administrator')
      else:
            if not ctypes.windll.shell32.IsUserAnAdmin():
                  raise Exception('ERROR: Must be run as root/administrator')

class Installer:
      def __init__(self):
            self._install_dir = None
            self._create_shortcut = False
      
      # PUBLIC FUNCTIONS #
      def install(self):
            if is_posix():
                  if self._install_dir is None:
                        self._install_dir = DEFAULT_INSTALL_DIR_POSIX

                  self._download_posix()
                  self._install_posix()
            else:
                  if self._install_dir is None:
                        self._install_dir = DEFAULT_INSTALL_DIR_WINDOWS
                  
                  self._download_windows()
                  self._install_windows()
      
      def update(self):
            pass

      # SETTERS #
      def set_install_dir(self, install_dir):
            self._install_dir = install_dir
      
      def set_create_shortcut(self, create_shortcut):
            self._create_shortcut = create_shortcut
      
      # PRIVATE FUNCTIONS #
      def _download_posix(self):
            urllib.request.urlretrieve(DOWNLOAD_URL_POSIX, '/tmp/')

      def _download_windows(self):
            urllib.request.urlretrieve(DOWNLOAD_URL_WINDOWS, 'C:\\Users\\Public\\')
      
      def _install_posix(self):
            


if __name__ == '__main__':
      run_installer()