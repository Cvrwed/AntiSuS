import requests

class Domain:
    def __init__(self, url):
        self.url = url

    def fetch(self):
        r = requests.get(self.url)
        return r.text.splitlines()

    def blacklist(self):
        pass

class Hentai(Domain):
    def blacklist(self):
        blocked_sites = self.fetch()
        with open("C:\\Windows\\System32\\drivers\\etc\\hosts", 'w+', encoding='utf-8', errors='strict') as hosts_file:
            for site in blocked_sites:
                if f"127.0.0.1     {site}" not in hosts_file.readlines():
                    hosts_file.write(f"127.0.0.1     {site}\n")
                    print(f"Blacklisted {site}")

def main():
    try:
        hentai = Hentai("https://raw.githubusercontent.com/zEncrypte/AntiSuS/main/domains-blacklisted.txt")
        hentai.blacklist()
        print("Finished blacklisting sites! Press any key to close")
    except (PermissionError):
        exit()
    
if __name__ == '__main__':
    main()
