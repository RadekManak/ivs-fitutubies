#
# Regular cron jobs for the calc package
#
0 4	* * *	root	[ -x /usr/bin/calc_maintenance ] && /usr/bin/calc_maintenance
