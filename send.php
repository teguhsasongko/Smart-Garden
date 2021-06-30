<?php
    //konek 
    $konek = mysqli_connect("localhost", "root", "", "sensor");

    //menerima datanya
    $kelembapan = $_GET['kelembapan'];
    $waterlevel = $_GET['waterlevel'];
    $menyiram = $_GET['menyiram'];

    //save
    mysqli_query($konek, "ALTER TABLE datasensor AUTO_INCREMENT=1");
    $simpan = mysqli_query($konek, "insert into datasensor(kelembapan, waterlevel, menyiram)values('$kelembapan','$waterlevel','$menyiram')");

    //test
    if($simpan)
    echo "BERHASIL GAESSSS";
    else
    echo "GAGAL CUK";
?>