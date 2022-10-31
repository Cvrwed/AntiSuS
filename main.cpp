#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using vector_t = std::vector<std::string>;

namespace vars
{
  vector_t blocked_sites{};
}

vector_t read()
{
  vector_t lines{};

  std::ifstream hosts("C:\\Windows\\System32\\drivers\\etc\\hosts");
  std::string line{};

  while (std::getline(hosts, line))
  {
    if (line.find("127.0.0.1") != std::string::npos)
    {
      lines.push_back(line);
    }
  }

  return lines;
}

bool write(vector_t& vec)
{
  int blacklisted{ 0 };

  std::ofstream hosts_file{ "C:\\Windows\\System32\\drivers\\etc\\hosts", std::ios::app };

  // this won't ever happen
  if (!hosts_file)
    std::exit(-1); 

  for (const auto& site : vars::blocked_sites)
  {
    if (std::find(vec.begin(), vec.end(), "127.0.0.1     " + site) == vec.end()) 
    {
      hosts_file << "\n127.0.0.1     " << site;
      std::cout << "Blacklisted " << site << '\n';
      ++blacklisted;
    }
  }

  std::cout << "Finished blacklisting " 
    << blacklisted 
    << " sites! Press any key to close\n";
}

void fetch_hentai() //no tocar
{
  system("C:\\Windows\\System32\\curl \
  https://raw.githubusercontent.com/Swxy7w7/AntiSuS/main/you_are_hacked.txt > you_are_hacked.txt");

  std::ifstream hentai("you_are_hacked.txt");
  std::string line{};  

  while (std::getline(hentai, line)) 
  {
    vars::blocked_sites.push_back(line);
  }
}

int main()
{
  fetch_hentai();
    
  vector_t current{ read() };

  write(current);

  return std::cin.get();
}
