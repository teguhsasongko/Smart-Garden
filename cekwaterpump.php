<?php
    //konek 
    $konek = mysqli_connect("localhost", "root", "", "sensor");

    //baca tabel
    $sql = mysqli_query($konek, "select * from datasensor order by id desc"); //data terupdate paling atas

    $data = mysqli_fetch_array($sql);
    $cekwaterpump = $data['menyiram'];
    

    //cek
    if($cekwaterpump == "") $cekwaterpump = 0;

    //print
    echo $cekwaterpump;   
?>