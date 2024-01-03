# Iterate from 1 to 10 and call make run with arg=x
for ($i = 146; $i -le 153; $i++) {
    & ./main c$i
}
# Set-ExecutionPolicy -Scope Process Bypass
# powershell -ExecutionPolicy Bypass -File ".\script.ps1"