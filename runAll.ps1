param (
    [char]$type,
    [int]$start,
    [int]$end
)

for ($test = $start; $test -le $end; $test++) {

    for ($heur = 0; $heur -le 3; $heur++) {
        & ./main $type$test $heur
    }
    Write-Host "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"

}

# .\runAll.ps1 -type 'c' -start 1 -end 10

# Set-ExecutionPolicy -Scope Process Bypass