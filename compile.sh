echo "\033[0;34m ======== Compiling Easy2D From Source ======== \033[0m"
echo "[Easy2D]: Creating build folder..."
mkdir -p build
echo "[Easy2D]: Compiling scripts..."
if sudo make ; then
  echo "\033[1;32m[Easy2D]: Successfully compiled scripts...\033[0m"
else
  echo "\033[1;31m[Easy2D]: An error occurred when compiling scripts...\033[0m"
fi

echo "[Easy2D]: Installing the library into system..."

if sudo make install ; then
  echo "\033[1;32m[Easy2D]: Successfully installed library to the system...\033[0m"
else
  echo "\033[1;31m[Easy2D]: An error occurred when installing the library...\033[0m"
fi

