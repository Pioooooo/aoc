set -e

apk add --no-cache -u build-base gdb --repository https://dl-cdn.alpinelinux.org/alpine/v3.19/main

mkdir -p ${_REMOTE_USER_HOME}/.config/gdb &&
	cat <<-EOF >${_REMOTE_USER_HOME}/.config/gdb/gdbinit
		python
		import sys
		sys.path.insert(0, '/usr/share/gcc-13.2.1/python')
		from libstdcxx.v6.printers import register_libstdcxx_printers
		register_libstdcxx_printers (None)
		end
	EOF

echo "alias g++='g++ -std=c++23'" >>${_REMOTE_USER_HOME}/.bashrc
