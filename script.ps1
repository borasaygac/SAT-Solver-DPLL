# Iterate from 1 to 10 and call make run with arg=x
for ($i = 1; $i -le 33; $i++) {
    & ./main t$i
}
# Set-ExecutionPolicy -Scope Process Bypass
