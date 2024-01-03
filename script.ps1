# Iterate from 1 to 10 and call make run with arg=x
param (
    [int]$start,
    [int]$end,
    [char]$type
)

for ($i = $start; $i -le $end; $i++) {
    & ./main $type$i
}
# .\script.ps1 -start 1 -end 10 -type 'c'
# Set-ExecutionPolicy -Scope Process Bypass
# powershell -ExecutionPolicy Bypass -File ".\script.ps1"