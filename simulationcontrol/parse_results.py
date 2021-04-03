import os
from tabulate import tabulate
from resultlib import *

def main():
    headers = [
        'date',
        'config',
        'tasks',
        #'sim. time (ns)',
        'avg resp time (ns)',
        'resp times (ns)',
    ]
    rows = []
    runs = sorted(list(get_runs()))
    for run in runs:
        if has_properly_finished(run):
            config = get_config(run)
            tasks = get_tasks(run)
            if len(tasks) > 40:
                tasks = tasks[:37] + '...'
            rows.append([
                get_date(run),
                config,
                tasks,
                #'{:,}'.format(get_total_simulation_time(run)),
                '{:,}'.format(get_average_response_time(run)),
                '  '.join('{:,}'.format(r) for r in get_individual_response_times(run)),
            ])
    print(tabulate(rows, headers=headers))


if __name__ == '__main__':
    main()
