<?php

function generator($districts,$max,$total,$state){
  include $state.".inc";
  $data = state_array();
  $result = '<h1>'.$state.'</h1><svg
     xmlns="http://www.w3.org/2000/svg"
     viewBox="0 0 297 210"
     version="1.1">
    <g
       transform="translate(0,-87)">
      <g
         transform="'.$data['matrix'].'"
         title="'.$state.'"
         entity_type="state">';
     // To separate the state name from $data array
     $key = array_keys($data);
     // To separate the states name from $districts array
     $key2 = array_keys($districts);
     $i=0;
     foreach ($data as $m) {
       $j=0;
       $flag = false;
       foreach ($districts as $s) {
         // Checking $districts's state name in $map
         if($key[$i]==$key2[$j]){
           $flag = $districts[$key2[$j]];
           break;
         }
         $j++;
       }
       // Generating individual data for each states
       if($flag){
         $result .= '<path id="'.$key[$i].'" fill ="'.$flag.'" class="state" onclick="state(\''.$key[$i].'\')" stroke="#FFFFFF" stroke-width="0.25850111" d="'.$m.'"><title>'.$key[$i].'</title></path>';
       }else {
         $result .= '<path id="'.$key[$i].'" fill = "#666666" class="state" onclick="state(\''.$key[$i].'\')" stroke="#FFFFFF" stroke-width="0.25850111" d="'.$m.'"><title>'.$key[$i].'</title></path>';
       }
       $i++;
     }
     $result .= '</g></g></svg>';

     return $result;
}


?>
