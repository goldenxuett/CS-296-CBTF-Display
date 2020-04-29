from bs4 import BeautifulSoup
import re
import json

with open("CBTFScheduler.html") as fp:
    soup = BeautifulSoup(fp, 'html.parser')
    list_of_dates = []
    start_date = True
    holder = []
    for tag in soup.find_all('td',string=re.compile('....-..-..')):
        if (start_date):
            holder.append(tag.string)
            start_date = False
        else: 
            holder.append(tag.string)
            list_of_dates.append(holder)
            holder = []
            start_date = True
    f = open("cbtf_dates.txt", "w")
    f.write(json.dumps(list_of_dates, sort_keys=True, indent=4))
    f.close