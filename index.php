<!doctype html>
<html lang="en">
  <head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">

    <title>SMART GARDEN!</title>
            <script type="text/javascript" src="jquery/jquery.min.js"></script>
            <!-- buat otomatis-->
            <script type="text/javascript">
                $(document).ready(function() {

                    setInterval(function(){
                        $("#cekkelembapan").load('cekkelembapan.php');
                    }, 1000 );
                });
                </script>

                <script type="text/javascript">
                $(document).ready(function() {

                    setInterval(function(){
                        $("#ceklevelair").load('ceklevelair.php');
                    }, 1000 );
                });
                </script>

                <script type="text/javascript">
                $(document).ready(function() {

                    setInterval(function(){
                        $("#cekwaterpump").load('cekwaterpump.php');
                    }, 1000 );
                });
                </script>

                <script type="text/javascript">
                $(document).ready(function() {

                    setInterval(function(){
                        $("#date").load('date.php');
                    }, 1000 );
                });
                </script>
  </head>
  <body>
    <div class="container" style="text-align: center; margin-top: 200px;">
    <h2>Monitoring Smart Garden</h2>
    <div style="display: flex;">
    <!-- menampilkan hasil sensoring-->
        <!-- Sensor Kelembapan-->
        <div class="card text-center" style="width: 33.33%">
            <div class="card-header" style="font-size: 30px; font-weight: bold;">
            KELEMBAPAN
            </div>
            <div class="card-body">
            <h1> <span id="cekkelembapan">0</span></h1>
            </div>
        </div> 
        <!-- akhir hasil kelembapan -->   
        <!-- Sensor level air-->
        <div class="card text-center" style="width: 33.33%">
            <div class="card-header" style="font-size: 30px; font-weight: bold;">
            Level Air
            </div>
            <div class="card-body">
            <h1><span id="ceklevelair">0</span> CM</h1>
            </div>
        </div>
        <!-- akhir hasil level air -->   
        <!-- Sensor level air-->
        <div class="card text-center" style="width: 33.33%">
        <div class="card-header" style="font-size: 30px; font-weight: bold;">
            WATER PUMP
            </div>
            <div class="card-body">
            <h1><span id="cekwaterpump">ON/OFF</span></h1>
            </div>
        </div>
        <!-- akhir hasil level air --> 
        
    <!-- akhir hasil -->
    </div>
        <!--Buat tanggal-->
            <div class="card text-white bg-dark mb-2" style="height: 5rem; weight: 10rem;">
            <div class="card-header">Waktu Update</div>
                <h5 class="card-title"><span id="date">JAM BERAPA INI?</span></h5>
            </div>
    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
  
    </body>
  <footer>www.teguhsasongko.id</footer>
</html>