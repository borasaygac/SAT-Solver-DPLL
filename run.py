import subprocess
import time
import sys


def param(type, start, end, heur=42, timeout_value=600):
    if heur == 42:
        for test in range(start, end + 1):
            for h in range(4):
                print(f'./main {type}{test} {h}')
                subprocess.run(['./main', f'{type}{test}', f'{h}'])
                time.sleep(1)
            print("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------")
    else:
        for i in range(start, end + 1):
            subprocess.run(['./main', f'{type}{i}', str(heur)])
            time.sleep(1)

if __name__ == "__main__":
    script_name, script_type, start_value, end_value, heur_value = sys.argv

    try:
        start_value, end_value, heur_value = map(int, (start_value, end_value, heur_value))
    except ValueError:
        print("Error: start, end, heur, and timeout must be integers.")
        sys.exit(1)

    param(script_type, start_value, end_value, heur_value)
