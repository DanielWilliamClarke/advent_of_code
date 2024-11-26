# AOC 2024 - Lua

## Install
Lua install:  https://stackoverflow.com/questions/73658960/how-can-i-install-lua-on-macos-monterey-without-admin-powers-and-terminal-acces
Luarocks install: https://github.com/luarocks/luarocks/wiki/Installation-instructions-for-Unix
Simple test: https://github.com/EvandroLG/simple_test

## Luarocks path config: 

1. Ensure LuaRocks Path Configuration
   LuaRocks installs modules into directories that Lua needs to know about. Verify that your Lua environment is set up to include these paths:

Check LuaRocks paths: Run:

```bash
luarocks path
```
This command will print the environment variables needed to find your installed rocks.

Set up environment variables: Copy the output of luarocks path and add it to your shell's configuration file (e.g., ~/.bashrc, ~/.zshrc). It usually looks something like this:

```bash
export LUA_PATH="$HOME/.luarocks/share/lua/5.4/?.lua;$HOME/.luarocks/share/lua/5.4/?/init.lua;$LUA_PATH"
export LUA_CPATH="$HOME/.luarocks/lib/lua/5.4/?.so;$LUA_CPATH"
```
Replace 5.4 with your Lua version.
