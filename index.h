
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE HTML><html>
  <head>
  
<style>
body {
  background-color: #fffff0;
}
</style>
 
    <title>ESP-Riders Web Server</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <style>
      body { font-family: Times; text-align: center; margin:1px auto; padding-top: 30px; width:auto; user-select: none;}
      
      
      .button{
        padding: 2px 2px;
        font-size: 18px;
        font-family: appaji ambarisha darbha;
        background-color: white;
        margin: 2px;
        color: black;
        border: 1px solid black;
        width: 150px;
        height: 50px;
        display: inline;
        text-align: center;
             }  
             
      .button:hover {
        background-color: white;
         color: grey;
                    }
                    
      .button:active {
        background-color: #007399;
        color: white;
        box-shadow: 2 1px #ff0045;
//        transform: translateY(x);
                    }
      
      .action_btn {
        width: 150px;
        margin: 0 auto;
        display: inline;}

.slidecontainer {
  width: 100%;
}

.slider {
  -webkit-appearance: none;
  width: 80%;
  height: 50px;
  background: #30ffff;
  outline: none;
  opacity: 1.0;
  -webkit-transition: .2s;
  transition: opacity .2s;
}

.slider:hover {
  opacity: 1;
}

.slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 50px;
  height: 50px;
  background: #edfcda;
  cursor: pointer;
}

.slider::-moz-range-thumb {
  width: 25px;
  height: 25px;
  background: #ffffff;
  cursor: pointer;
}
  
  </style>
    <body style="background-color: #1c8eff">
    
  </head>
  <body>
    <h1>ESP-RIDER-Big-Chassis</h1>

    <button class="button" id="button1" ontouchstart="toggle('A');" ontouchend="toggle('off');">Forward Fast</button>
    
    <button class="button" id="button2" ontouchstart="toggle('B');" ontouchend="toggle('off');">Forward</button>
    
    <button class="button" id="button3" ontouchstart="toggle('C');" ontouchend="toggle('off');">Reverse</button>
    
    <button class="button" id="button4" ontouchstart="toggle('D');" ontouchend="toggle('off');">Retros</button>

<div class="buttons">
<div class="action_btn">
    
    <p><button class="button" id="button5"  ontouchstart="toggle('L');" ontouchend="toggle('FO');">Left</button>
    
    <button class="button" id="button6"  ontouchstart="toggle('R');" " ontouchend="toggle('FO');" >Right</button></p>
             </div>

        </div>
<div class="slidecontainer">

    <p>  </p>
  
  <input type="range" min="70" max="110" value="90" class="slider" id="myRange">
   
</div>

<script>

var slider = document.getElementById("myRange");
slider.oninput = function() {
  pos = slider.value;
  steering(pos);
}
</script>
      
<script>
   
   function toggle(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/" + x, true);
     xhr.send();
   }

   function steering(pos) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/Pos?value="+ pos , true);
     xhr.send();
   }
  
  </script>
  </body>
</html>
)=====";
