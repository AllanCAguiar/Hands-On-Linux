savedcmd_probe_2025.mod := printf '%s\n'   probe_2025.o | awk '!x[$$0]++ { print("./"$$0) }' > probe_2025.mod
