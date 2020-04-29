#
# Regular cron jobs for the fitutubiescalculator package
#
0 4	* * *	root	[ -x /usr/bin/fitutubiescalculator_maintenance ] && /usr/bin/fitutubiescalculator_maintenance
