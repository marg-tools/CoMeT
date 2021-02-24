<?php

$image_1 = imagecreatefrompng('compute.png');
$image_2 = imagecreatefrompng('mem.png');
imagealphablending($image_1, true);
imagesavealpha($image_1, true);
imagecopy($image_1, $image_2, 0, 0, 50, 50, 100, 100);
imagepng($image_1, 'image_3.png');

?>

