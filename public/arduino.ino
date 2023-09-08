#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "MIC_2.4GHz";
const char* password = "999999999";

WebServer server(80);   // พร้อมสร้างเว็บเซิร์ฟเวอร์

void setup() 
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);   // เชื่อมต่อ WiFi

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());    // แสดง IP address ของบอร์ด Arduino

  server.on("/", []() {
    String html = "<html><body>";
    html += "<h1>ModbusRTU</h1>";
    html += "<form>";
    for (int i = 0; i < 10; i++) {
      html += "<label for=\"Input" + String(i) + "\">Input " + String(i) + ":</label>";
      html += "<input type=\"text\" id=\"input" + String(i) + "\" name=\"input" + String(i) + "\"><br><br>";
    }
    html += "<button type=\"button\" onclick=\"sendData()\">Submit</button>";
    html += "</form>";
    html += "<script>";
    html += "function sendData() {";
    html += "  var inputs = [];";
    for (int i = 0; i < 10; i++) {
      html += "  var input" + String(i) + " = document.getElementById('input" + String(i) + "').value;";
      html += "  inputs.push(input" + String(i) + ");";
    }
    html += "  var xhttp = new XMLHttpRequest();";
    html += "  xhttp.onreadystatechange = function() {";
    html += "    if (this.readyState == 4 && this.status == 200) {";
    html += "      console.log(this.responseText);";
    html += "    }";
    html += "  };";
    html += "  xhttp.open(\"GET\", \"/submit?input0=\" + inputs[0]";
    for (int i = 1; i < 10; i++) {
      html += "+\"&input" + String(i) + "=\" + inputs[" + String(i) + "]";
    }
    html += ", true);";
    html += "  xhttp.send();";
    html += "}";
    html += "</script>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/submit", []() {
    for (int i = 0; i < 10; i++) {
      if (server.argName(i).startsWith("input")) {
        String value = server.arg(i);
        Serial.print("Input " + String(i) + ": ");
        Serial.println(value);
      }
    }
    server.send(200, "text/plain", "OK");
  });



  server.begin();   // เริ่มต้นเซิร์ฟเวอร์
}

void loop() {
  server.handleClient();   // รอรับและตอบกลับคำขอจาก client
}