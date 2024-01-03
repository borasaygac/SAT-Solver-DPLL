# Iterate from 1 to 10 and call make run with arg=x
param (
    [int]$start,
    [int]$end,
    [char]$type
)

for ($i = $start; $i -le $end; $i++) {
    & ./main $type$i 
    # Start-Sleep -Milliseconds 500 # Add a half-second (500 milliseconds) delay
}
# .\script.ps1 -start 1 -end 10 -type 'c'
# Set-ExecutionPolicy -Scope Process Bypass
# powershell -ExecutionPolicy Bypass -File ".\script.ps1"
