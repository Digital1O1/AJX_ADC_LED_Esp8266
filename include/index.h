const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<title>W3.CSS</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css"> 
<style>
  /*
      Sets h1<>, paragraphs and div tags to center align text
  */
  h1 {text-align: center;}
  p {text-align: center;}
  div {text-align: center;}
</style>

<body>
<!-- 
    <div id="demo"
      - Gives an ID attribute to the current HTML element
      - ID defines the element uniquely so it can be used in Javascript 
-->
<div id="demo">
<h1>LED/ADC Ajax Example</h1>
	<button type="button" onclick="sendData(1)">LED ON</button>
	<button type="button" onclick="sendData(0)">LED OFF</button><BR>
  <br>ADC Value is : <span id="ADCValue">0</span><br>
  <br>Random number generated : <span id="randomNum">0</span><br>
  <br>LED State is : <span id="LEDState">NA</span>

<br>
</div>

<div class="w3-light-grey">
  <div id="myBar" class="w3-container w3-green" style="height:24px;width:1%"></div>
  
</div>

<button class="w3-button w3-light-grey" onclick="move()">Click Me</button>
<br>TEST 2 : <span id="randomNum2">0</span><br>



<!--HTML ends here-->

<script>
  // Bar Graph
  
  function move() 
  {  
    ///*
    var elem = document.getElementById("myBar");
    var width = 1;
    var id = setInterval(frame, 10);
    function frame() 
    {
      if (width >= 100) 
      {
        clearInterval(id);
      } 
      else 
      {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() 
        {
          if (this.readyState == 4 && this.status == 200) 
          {
            document.getElementById("randomNum2").innerHTML = this.responseText;
            elem.style.width = document.getElementById("randomNum2").innerHTML + '%';

          }
        };
        xhttp.open("GET", "/randomNum2", true);
        xhttp.send();          

        width++;
        //elem.style.width = width + '%';
      }
    }
    //*/
   // Display random number values generated from ESP8266

}

function sendData(led) 
{
  /*
      new XMLHttpRequest();
        - Reference link : https://www.w3schools.com/js/js_ajax_http.asp
        - Used to exchange data with webserver behind the scenes
  */

  // Create XMLHttpRequest Object
  var xhttp = new XMLHttpRequest();
  /*
      Define a Callback Function xhttp.onreadystatechange = function() 
        - xhttp.onreadystatechange = function() 
        - What's a callback function 
          - A function that's passed as a parameter to another function
          - Should have the code to execute when the response is ready
  */

  // Another callback function
  xhttp.onreadystatechange = function() 
  {
    if (this.readyState == 4 && this.status == 200) 
    {
      /*
        this.readyState
          - Reference : https://developer.mozilla.org/en-US/docs/Web/API/XMLHttpRequest/readyState
          - Returns the state an XMLHttpRequest client
          - Value |	  State	           |  Description
            -------------------------------------------------------------------------------------------
            0	    |   UNSENT	         |  Client has been created. open() not called yet.
            1	    |   OPENED	         |  open() has been called.
            2	    |   HEADERS_RECEIVED |  send() has been called, and headers and status are available.
            3	    |   LOADING	         |  Downloading; responseText holds partial data.
            4	    |   DONE	           |  The operation is complete.

        this.status
            - 200: "OK"
            - 403: "Forbidden"
            - 404: "Page not found"
          
            getElementById()
            - Used every time you want to manipulate/get info 
              from an element in your document

            this.responseText
              -Returns the server response as a JavaScript string
              - Contains content from the requested URL using the XMLHttpRequest
              - 
      */
      document.getElementById("LEDState").innerHTML =
      this.responseText;
    }
  };
  /*
      xhttp.open()  
        - Reference link : https://www.w3schools.com/xml/ajax_xmlhttprequest_send.asp
        - What does it do
          - Sends request to server
        - Parameters
          - open(method,url,async)
            - Specifies the type of request
            - Method : The type of request -> GET or POST
            - URL    : The server (file) location
            - Async : true (Asynchronous) | false (synchronous)
          - The '+led'
            - Is considered a 'Unique ID'
            - Used to avoid getting a cahced result
              - cahced result : Area of memory that stores the result of a 
                DB query/query block for resue
  */
  xhttp.open("GET", "setLED?LEDstate="+led, true);
  /*
    xhttp.send();
      - send()
        - Sends request to server 
        - Used for GET requests
      - send(string)
        - Sends request to server
        - Used for POST requests
  */
  xhttp.send();
}

setInterval(function() 
{
  // Call a function repetatively with 500ms Second interval
  getData();
  //move();
}, 500); //500mSeconds update rate

function getData() 
{
  // Read ADC
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() 
  {
    if (this.readyState == 4 && this.status == 200) 
    {
      document.getElementById("ADCValue").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/readADC", true);
  xhttp.send();

  // Display random number values generated from ESP8266
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() 
  {
    if (this.readyState == 4 && this.status == 200) 
    {
      document.getElementById("randomNum").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/randomNum", true);
  xhttp.send();
}

</script>
</body>
</html>
)=====";