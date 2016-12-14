#!/usr/bin/env python2
from lib_scrapper import *
path_dir_download = "./"
url = "https://dev.socrata.com/foundry/data.chattlibrary.org/sahz-tkbn"
xpath = ".//*[contains(@class,'download')]/div[3]/a"
city = "chattanooga"
# If this script no longer fetches any results check the XPath


def main():
    os.chdir(path_dir_download)
    br = start_browser()
    go_to_page(br,url)
    time.sleep(2)
    elements = find_elements(br,xpath)
    links = find_links(elements)
    close_browser(br)
    content = get_log(city,path_dir_download)
    download_links = rm_same(links, content)
    download_links=download_links[0].split("?")
    download_links.remove(download_links[1])
    download_links = download(download_links)
    add_log(download_links,city,path_dir_download)
    unzip(path_dir_download)  
    clean(path_dir_download)      

main()
