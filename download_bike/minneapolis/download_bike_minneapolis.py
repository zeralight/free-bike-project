#!/usr/bin/env python2
from lib_scrapper import *
path_dir_download = "./"
url = "https://www.niceridemn.org/data/"
xpath = ".//h3[contains(text(),'Historic Data')]/following-sibling::p/a"
city = "minneapolis"
# If this script no longer fetches any results check the XPath


def main():
    os.chdir(path_dir_download)
    br = start_browser()
    go_to_page(br,url)
    elements = find_elements(br,xpath)
    links = find_links(elements)
    close_browser(br)
    content = get_log(city,path_dir_download)
    for i in range(len(links)) :
        links[i]=links[i].replace("/dl/","/dd/")+"/"+links[i].split("/")[-1]+".zip"
    download_links = rm_same(links, content)
    download_links = download(download_links)
    add_log(download_links,city,path_dir_download)
    unzip(path_dir_download)
    clean(path_dir_download)
        
main()
