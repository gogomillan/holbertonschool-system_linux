#!/bin/sh
# The requirement is for running in sh
# Using: kill -l
# SIGABRT(bash) -> ABRT(sh)
# SIGIO(bash) -> IO(sh)
# SIGTERM(bash) -> SIGTERM(sh)
trap "echo Nope" ABRT IO TERM
