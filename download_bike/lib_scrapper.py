from selenium import webdriver
import os
import time

def start_browser():
    """
   Starts a selenium browser and return a pointer on it.
    """
    br = webdriver.Firefox()
    print(".browser started")
    return br

def close_browser(br):
    """
    Close the br selenium browser.
    """

    br.quit()
    print(".browser closed")


def go_to_page(br, url):
    """
    Load the url on the browser br.
    """
    br.get(url)
    time.sleep(2)

def find_elements(br, xpath):
    """
    Return a list of elements (selenium object) using the xpath given.  
    """
    return br.find_elements_by_xpath(xpath)

def find_links(elements):
    """
    From a list of elements return a list of url corresponding to the attribute href of each element (each element has to have an attribute href).
    """
    links = []
    for element in elements :
        links.append(str(element.get_attribute("href")))
    return list(set(links))

def get_log(city,path_dir):
    """
    Return a list of string, each string corresponding to one line of the file 'city'_log in the directory pointed by path_dir.
    """
    if not os.path.isfile(path_dir+city+"_log") :
        os.system("touch "+path_dir+city+"_log")
    with open(path_dir+city+"_log",'r') as log :
        content = str(log.read())
        content = content.split("\n")    
        log.close()
    return content
    
def rm_same(links, content):
    """
    From two list of string strip the first list from each string wich is already present in the second then return this string.
    """
    rm = []
    for link in links :
        for word in content :
            if link in word :
                rm.append(link)
                break
    for link in rm:
        links.remove(link)
    return links

def add_log(links,city, path_dir):
    """
    Add lines in the file 'city'_log in the directory pointed by path_dir, each line is one string in the list of string links.
    """
    with open(path_dir+city+"_log",'a') as log :
        for link in links :
            log.write(link+"\n")
        log.close()

def download(links):
    """
    Try to download each link in the list of string links, then return the list of links without the ones we couldn't download.
    """
    rm=[]
    for link in links :
        if os.system("wget "+link) != 0 :
            print "Error for : " + link           
            rm.append(link)
            temp  = link.split('/')
            os.system("rm "+temp[-1])
    for link in rm :
        links.remove(link)
    return links

def unzip(path_dir):
    """
    Unzip each files in the directory pointed by path_dir then remove them.
    """
    files = os.listdir(path_dir)
    for f in files :
        if ".zip" in f:
            os.system("unzip "+path_dir+f)
    os.system("rm "+path_dir+"*.zip")
    os.system("mv "+path_dir+"*/*.csv "+path_dir)

def clean(path_dir):
    files = os.listdir(path_dir)
    for f in files:
        if not ".csv" in f:
            if not "_log" in f:
                if not ".py" in f:
                    os.system("rm -rf "+path_dir+f)
