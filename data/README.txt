
Network topology and flows of a large european ISP (internet service provider).

Router names are anonymized to random four-digit numbers starting from 1000.
Router coordinates has been shifted and randomly blurred. Each router is tagged as either an 'internal' or a 'customer' router.
Link capacities (bytes per timeunit), and link utilization and flow traffic (bytes per timeunit, averaged over an hour) are scaled to fit between 0 and 1000000 (for anonymization).
Link utilization and flow traffic are aggregated over an hour. The files with flow paths list all paths used by a flow. Flow paths are mostly stable, but there are some changes over time. Paths are reported per hour. Only flows with non-zero traffic in that hour are included in the flow path file.
Each file with Link utilization, flow traffic and flow paths contains data for 24 hours of one day. The dataset contains seven days of a week (Monday to Sunday) - in seperate files to make it easier to get started with analysis of just one day.

The files are gzip compressed CSV files. 
(Hint: on Linux you can use 'less' to inspect .gz files.)
(Hint: to combine files use e.g.: 'zcat link-util-day{1,2,3,4,5,6,7}.csv.gz | gzip > link-util-week.csv.gz')

Example of data import in Python:
    import pandas as pd
    import networkx as nx
    links = pd.read_csv('links.csv.gz', compression='gzip')
    graph = nx.from_pandas_edgelist(links, source='linkStart', target='linkEnd', edge_attr='capacity')
    routers = pd.read_csv('routers.csv', index_col='router')
    
    link_utils_header = ['timestamp','linkStart','linkEnd','avgUtilization']
    link_utils = pd.read_csv('link-util-day1.csv.gz', compression='gzip', names=link_utils_header, parse_dates=['timestamp'])

    flows_header = ['timestamp','origin','destination','avgTraffic']
    flows = pd.read_csv('flow-traffic-day1.csv.gz', compression='gzip', names=flows_header, parse_dates=['timestamp'])
    
    paths_header = ['timestamp','origin','destination','path']
    # Next line crashes with 32 GB memory. Consider using a different approach to parsing, e.g. parse and process just one flow at a time. And consider using e.g. C++ for this.
    paths = pd.read_csv('flow-paths-day1.csv.gz', compression='gzip', names=paths_header, parse_dates=['timestamp'], converters={'path': lambda x: x.strip('[]').split(';')})

