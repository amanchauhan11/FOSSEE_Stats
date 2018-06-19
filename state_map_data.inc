<?php

function state_map_data($type,$activities,$status,$state){

  $state_id = db_select('states','s')
    ->fields('s', array('id'))
    ->condition('name',$state)
    ->execute()
    ->fetchField();

  $district_list = db_select('districts','d')
    ->fields('d', array('name'))
    ->condition('state_id',$state_id)
    ->execute();
  $districts = array();

  while($each = $district_list->fetchObject()){
    $districts[$each->name] = 0;
  }
  /* For separation of state name from key of $states array */
  $key = array_keys($districts);
  /* Checking the foss type */
  if($type == "" || $type == NULL){
    $query = db_select('foss_type','u')
      ->fields('u', array(
        'tbc',
        'foss_name',
        'lab_migration',
        'workshop',
        'conference',
        '$foss_selfworkshop_no'
      ))
      ->execute();
      /* For fetching data from all foss type */
      while($foss = $query->fetchObject()){
        $name = $foss->foss_name;
        //echo '<h1>'.$name.'</h1>';
        // Workshop
        if($foss->workshop){
          $query1 = db_select('workshop', 'w')
            ->fields('w', array('pincode'))
            ->condition('type','workshop')
            ->condition('foss_name',$name)
            ->condition('state',$state)
            ->execute()
            ->fetchAll();
          // Assigning to each states
          foreach ($query1 as $s) {
            $district = db_select('ai_pincode','a')
              ->fields('a', array('districtname'))
              ->condition('pincode',$s->pincode)
              ->execute()
              ->fetchField();
            $districts[$district]++;
          }
        }
        //echo '<br>Workshop<br>';
        //print_r($districts);
        // Conference
        if($foss->conference){
          $query1 = db_select('workshop', 'w')
            ->fields('w', array('pincode'))
            ->condition('type','conference')
            ->condition('foss_name',$name)
            ->condition('state',$state)
            ->execute()
            ->fetchAll();
          // Assigning to each states
          foreach ($query1 as $s) {
            $district = db_select('ai_pincode','a')
              ->fields('a', array('districtname'))
              ->condition('pincode',$s->pincode)
              ->execute()
              ->fetchField();
            $districts[$district]++;
          }
        }
        //echo '<br>Conference<br>';
        //print_r($districts);

        // Text Book companion
        db_set_active($name);
        if($foss->tbc){
          if ($name != 'Python') {
              $query2 = db_query("SELECT po.pincode AS pin FROM {textbook_companion_preference} pe LEFT JOIN {textbook_companion_proposal} po ON pe.proposal_id = po.id WHERE pe.approval_status =1 AND pe.category>0 AND po.state LIKE :state", array(
                  ':state' => $state,
              ));
              db_set_active('default');
              while($pin = $query2->fetchObject()->pin) {
                $district = db_select('ai_pincode','a')
                  ->fields('a', array('districtname'))
                  ->condition('pincode',$pin)
                  ->execute()
                  ->fetchField();
                $districts[$district]++;
              }
              db_set_active($name);
          }
          else {
              /*$query5 = db_select('tbc_book');
              $query5->addExpression('count(*)', 'count');
              $query5->condition('approved', 1);
              $result5 = $query5->execute();
              $completedbookcount += $result5->fetchObject()->count;
              $query6 = db_select('tbc_book');
              $query6->addExpression('count(*)', 'count');
              $query6->condition('approved', 1, '<>');
              $result6 = $query6->execute();
              $pendingbookcount += $result6->fetchObject()->count;*/
          }
        }
        //echo '<br>TBC<br>';
        //print_r($districts);

        // Lab Migration
        if($foss->lab_migration){
          /* Completed Lab Migration */
          $query1 = db_select('lab_migration_proposal','u')
            ->fields('u', array('pincode'))
            ->condition('approval_status', 2,'!=')
            ->condition('state',$state)
            ->execute()
            ->fetchAll();
          db_set_active('default');
          foreach ($query1 as $s) {
            $district = db_select('ai_pincode','a')
              ->fields('a', array('districtname'))
              ->condition('pincode',$s->pincode)
              ->execute()
              ->fetchField();
            $districts[$district]++;
          }
          db_set_active($name);
        }
        //echo '<br>LM<br>';
        //print_r($districts);
        /*
        //  Self Workshop space
        if($foss->foss_selfworkshop_no){
          db_set_active('selfworkshop');
          foreach ($key as $k) {
            $query2 = db_query("SELECT count(t.id) as count FROM {events_training} t, {events_academiccenter} ac, {events_city} c, {events_state} s WHERE t.academic_id=ac.id and ac.city_id=c.id and c.state_id=s.id and (t.status = 4 AND t.foss_id = :foss_id ) and s.name LIKE :state ", array(
              ':foss_id' => $foss->foss_selfworkshop_no,
              ':state'=>$k
            ));
            $states[$k] += $query2->fetchObject()->count;
          }

        }
        */
        /* DWSIM Flowsheet */
        if($name == 'DWSIM'){
          db_set_active('DWSIM');
          $query1 = db_select('dwsim_flowsheet_proposal','d')
            ->fields('d', array('pincode'))
            ->condition('approval_status', 2,'!=')
            ->condition('state',$state)
            ->execute()
            ->fetchAll();
          db_set_active('default');
          foreach ($query1 as $s) {
            $district = db_select('ai_pincode','a')
              ->fields('a', array('districtname'))
              ->condition('pincode',$s->pincode)
              ->execute()
              ->fetchField();
            $districts[$district]++;
          }
          db_set_active($name);
        /* eSim Circuit Simulation */
        }else if($name == 'eSim'){
          db_set_active('eSim');
          $query1 = db_select('esim_circuit_simulation_proposal','e')
            ->fields('e', array('pincode'))
            ->condition('approval_status', 2,'!=')
            ->condition('state',$state)
            ->execute()
            ->fetchAll();
          db_set_active('default');
          foreach ($query1 as $s) {
            $district = db_select('ai_pincode','a')
              ->fields('a', array('districtname'))
              ->condition('pincode',$s->pincode)
              ->execute()
              ->fetchField();
            $districts[$district]++;
          }
          db_set_active($name);
        }
        //echo '<br>Final<br>';
        //print_r($districts);
        db_set_active('default');
        db_set_active();
      }
  }else{
    $query = db_select('foss_type','u')
      ->fields('u', array(
        'tbc',
        'foss_name',
        'lab_migration',
        'workshop',
        'conference',
        'foss_selfworkshop_no',
        'flow_sheet',
        'circuit_simulation',
        'case_study'
      ))
      ->condition('id',$type)
      ->execute()
      ->fetchObject();
    $name = $query->foss_name;
    /* Converting ID to name of Activities */
    $options = get_activities_list($type);
    for ($i=0; $i <= max(array_keys($options)) ; $i++) {
      if ($i == $activities) {
        $act = $options[$i];
      }
    }
    /* When Activities are set */
    if ($activities != 0) {
      /* Converting ID to name of Activities */
      $options = _ajax_example_get_third_dropdown_options($activities);
      for ($i=0; $i <= max(array_keys($options)) ; $i++) {
        if ($i == $status) {
          $stat = $options[$i];
        }
      }
      /* When Status are set */
      if ($status != 0) {
        /* Book in Progress for Textbook Companion */
        if ($act == 'Textbook Companion' && $stat == 'Books in Progress') {
          db_set_active($name);
          if($query->tbc){
            if ($name != 'Python') {
                /* Pending Textbook Companion */
                $query3 = db_query("SELECT po.pincode AS pin FROM {textbook_companion_preference} pe LEFT JOIN {textbook_companion_proposal} po ON pe.proposal_id = po.id WHERE po.proposal_status <> 3 AND pe.approval_status =1 AND pe.category>0 AND po.state LIKE :state", array(
                    ':state' => $state
                ));
                db_set_active('default');
                while($pin = $query3->fetchObject()->pin) {
                  $district = db_select('ai_pincode','a')
                    ->fields('a', array('districtname'))
                    ->condition('pincode',$pin)
                    ->execute()
                    ->fetchField();
                  $districts[$district]++;
                }
                db_set_active($name);
            }
            else {
                /*$query5 = db_select('tbc_book');
                $query5->addExpression('count(*)', 'count');
                $query5->condition('approved', 1);
                $result5 = $query5->execute();
                $completedbookcount += $result5->fetchObject()->count;
                $query6 = db_select('tbc_book');
                $query6->addExpression('count(*)', 'count');
                $query6->condition('approved', 1, '<>');
                $result6 = $query6->execute();
                $pendingbookcount += $result6->fetchObject()->count;*/
            }
          }
        /* Completed Books for Textbook Companion */
        }elseif ($act == 'Textbook Companion' && $stat == 'Completed Books') {
          db_set_active($name);
          if($query->tbc){
            if ($name != 'Python') {
                /* Completed Textbook Companion */
                $query2 = db_query("SELECT po.pincode AS pin FROM {textbook_companion_preference} pe LEFT JOIN {textbook_companion_proposal} po ON pe.proposal_id = po.id WHERE po.proposal_status = 3 AND pe.approval_status =1 AND pe.category>0 AND po.state LIKE :state", array(
                    ':state' => $state,
                ));
                db_set_active('default');
                while($pin = $query2->fetchObject()->pin) {
                  $district = db_select('ai_pincode','a')
                    ->fields('a', array('districtname'))
                    ->condition('pincode',$pin)
                    ->execute()
                    ->fetchField();
                  $districts[$district]++;
                }
                db_set_active($name);
            }else {
                /*$query5 = db_select('tbc_book');
                $query5->addExpression('count(*)', 'count');
                $query5->condition('approved', 1);
                $result5 = $query5->execute();
                $completedbookcount += $result5->fetchObject()->count;
                $query6 = db_select('tbc_book');
                $query6->addExpression('count(*)', 'count');
                $query6->condition('approved', 1, '<>');
                $result6 = $query6->execute();
                $pendingbookcount += $result6->fetchObject()->count;*/
            }
          }
        /* Labs in Progress for Lab Migration */
        }elseif ($act == 'Lab Migration' && $stat == 'Labs in Progress') {
          db_set_active($name);
          if($query->lab_migration){
            $query1 = db_select('lab_migration_proposal','u')
              ->fields('u', array('pincode'))
              ->condition('approval_status', 1)
              ->condition('state',$state)
              ->execute()
              ->fetchAll();
            db_set_active('default');
            foreach ($query1 as $s) {
              $district = db_select('ai_pincode','a')
                ->fields('a', array('districtname'))
                ->condition('pincode',$s->pincode)
                ->execute()
                ->fetchField();
              $districts[$district]++;
            }
            db_set_active($name);
          }
        /* Completed Labs for Lab Migration */
        }elseif ($act == 'Lab Migration' && $stat == 'Completed Labs') {
          db_set_active($name);
          if($query->lab_migration){
            $query1 = db_select('lab_migration_proposal','u')
              ->fields('u', array('pincode'))
              ->condition('approval_status', 3)
              ->condition('state',$state)
              ->execute()
              ->fetchAll();
            db_set_active('default');
            foreach ($query1 as $s) {
              $district = db_select('ai_pincode','a')
                ->fields('a', array('districtname'))
                ->condition('pincode',$s->pincode)
                ->execute()
                ->fetchField();
              $districts[$district]++;
            }
            db_set_active($name);
          }
        }elseif ($act == 'Flowsheet' && $stat == 'Flowsheets in Progress') {
          db_set_active('DWSIM');
          $query1 = db_select('dwsim_flowsheet_proposal','d')
            ->fields('d', array('pincode'))
            ->condition('approval_status', 1)
            ->condition('state',$state)
            ->execute()
            ->fetchAll();
          db_set_active('default');
          foreach ($query1 as $s) {
            $district = db_select('ai_pincode','a')
              ->fields('a', array('districtname'))
              ->condition('pincode',$s->pincode)
              ->execute()
              ->fetchField();
            $districts[$district]++;
          }
          db_set_active($name);
        }elseif ($act == 'Flowsheet' && $stat == 'Completed Flowsheets') {
          db_set_active('DWSIM');
          $query1 = db_select('dwsim_flowsheet_proposal','d')
            ->fields('d', array('pincode'))
            ->condition('approval_status', 3)
            ->condition('state',$state)
            ->execute()
            ->fetchAll();
          db_set_active('default');
          foreach ($query1 as $s) {
            $district = db_select('ai_pincode','a')
              ->fields('a', array('districtname'))
              ->condition('pincode',$s->pincode)
              ->execute()
              ->fetchField();
            $districts[$district]++;
          }
          db_set_active($name);
        }elseif ($act == 'Circuit Simulation' && $stat == 'Simulations in Progress') {
          db_set_active('eSim');
          $query1 = db_select('esim_circuit_simulation_proposal','e')
            ->fields('e', array('pincode'))
            ->condition('approval_status', 1)
            ->condition('state',$state)
            ->execute()
            ->fetchAll();
          db_set_active('default');
          foreach ($query1 as $s) {
            $district = db_select('ai_pincode','a')
              ->fields('a', array('districtname'))
              ->condition('pincode',$s->pincode)
              ->execute()
              ->fetchField();
            $districts[$district]++;
          }
          db_set_active($name);
        }elseif ($act == 'Circuit Simulation' && $stat == 'Completed Simulations') {
          db_set_active('eSim');
          $query1 = db_select('esim_circuit_simulation_proposal','e')
            ->fields('e', array('pincode'))
            ->condition('approval_status', 3)
            ->condition('state',$state)
            ->execute()
            ->fetchAll();
          db_set_active('default');
          foreach ($query1 as $s) {
            $district = db_select('ai_pincode','a')
              ->fields('a', array('districtname'))
              ->condition('pincode',$s->pincode)
              ->execute()
              ->fetchField();
            $districts[$district]++;
          }
          db_set_active($name);
        }
      /* When status not set */
      }else {
        // Workshop
        if ($act == 'Workshop') {
          if($query->workshop){
            $query1 = db_select('workshop', 'w')
              ->fields('w', array('pincode'))
              ->condition('type','workshop')
              ->condition('foss_name',$name)
              ->condition('state',$state)
              ->execute()
              ->fetchAll();
            // Assigning to each states
            foreach ($query1 as $s) {
              $district = db_select('ai_pincode','a')
                ->fields('a', array('districtname'))
                ->condition('pincode',$s->pincode)
                ->execute()
                ->fetchField();
              $districts[$district]++;
            }
          }
        // Conference
        }elseif ($act == 'Conference') {
          if($query->conference){
            $query1 = db_select('workshop', 'w')
              ->fields('w', array('pincode'))
              ->condition('type','conference')
              ->condition('foss_name',$name)
              ->condition('state',$state)
              ->execute()
              ->fetchAll();
            // Assigning to each states
            foreach ($query1 as $s) {
              $district = db_select('ai_pincode','a')
                ->fields('a', array('districtname'))
                ->condition('pincode',$s->pincode)
                ->execute()
                ->fetchField();
              $districts[$district]++;
            }
          }
        // Textbook  Companion
        }elseif ($act == 'Textbook Companion') {
          db_set_active($name);
          if($query->tbc){

            if ($name != 'Python') {
              $query2 = db_query("SELECT po.pincode AS pin FROM {textbook_companion_preference} pe LEFT JOIN {textbook_companion_proposal} po ON pe.proposal_id = po.id WHERE pe.approval_status =1 AND pe.category>0 AND po.state LIKE :state", array(
                  ':state' => $state,
              ));
              db_set_active('default');
              while($pin = $query2->fetchObject()->pin) {
                $district = db_select('ai_pincode','a')
                  ->fields('a', array('districtname'))
                  ->condition('pincode',$pin)
                  ->execute()
                  ->fetchField();
                $districts[$district]++;
              }
              db_set_active($name);
            }
            else {
                /*$query5 = db_select('tbc_book');
                $query5->addExpression('count(*)', 'count');
                $query5->condition('approved', 1);
                $result5 = $query5->execute();
                $completedbookcount += $result5->fetchObject()->count;
                $query6 = db_select('tbc_book');
                $query6->addExpression('count(*)', 'count');
                $query6->condition('approved', 1, '<>');
                $result6 = $query6->execute();
                $pendingbookcount += $result6->fetchObject()->count;*/
            }
          }
        // Lab Migration
        }elseif ($act == 'Lab Migration') {
          db_set_active($name);
          if($query->lab_migration){
            $query1 = db_select('lab_migration_proposal','u')
              ->fields('u', array('pincode'))
              ->condition('approval_status', 2,'!=')
              ->condition('state',$state)
              ->execute()
              ->fetchAll();
            db_set_active('default');
            foreach ($query1 as $s) {
              $district = db_select('ai_pincode','a')
                ->fields('a', array('districtname'))
                ->condition('pincode',$s->pincode)
                ->execute()
                ->fetchField();
              $districts[$district]++;
            }
            db_set_active($name);
          }
        }elseif ($act == "Flowsheet") {
          db_set_active('DWSIM');
          $query1 = db_select('dwsim_flowsheet_proposal','d')
            ->fields('d', array('pincode'))
            ->condition('approval_status', 2,'!=')
            ->condition('state',$state)
            ->execute()
            ->fetchAll();
          db_set_active('default');
          foreach ($query1 as $s) {
            $district = db_select('ai_pincode','a')
              ->fields('a', array('districtname'))
              ->condition('pincode',$s->pincode)
              ->execute()
              ->fetchField();
            $districts[$district]++;
          }
          db_set_active($name);
        }elseif ($act == "Circuit Simulation") {
          db_set_active('eSim');
          $query1 = db_select('esim_circuit_simulation_proposal','e')
            ->fields('e', array('pincode'))
            ->condition('approval_status', 2,'!=')
            ->condition('state',$state)
            ->execute()
            ->fetchAll();
          db_set_active('default');
          foreach ($query1 as $s) {
            $district = db_select('ai_pincode','a')
              ->fields('a', array('districtname'))
              ->condition('pincode',$s->pincode)
              ->execute()
              ->fetchField();
            $districts[$district]++;
          }
          db_set_active($name);
        }
      }
    }else {
      // Workshop
      if($query->workshop){
        $query1 = db_select('workshop', 'w')
          ->fields('w', array('pincode'))
          ->condition('type','workshop')
          ->condition('foss_name',$name)
          ->condition('state',$state)
          ->execute()
          ->fetchAll();
        // Assigning to each states
        foreach ($query1 as $s) {
          $district = db_select('ai_pincode','a')
            ->fields('a', array('districtname'))
            ->condition('pincode',$s->pincode)
            ->execute()
            ->fetchField();
          $districts[$district]++;
        }
      }
      // Conference
      if($query->conference){
        $query1 = db_select('workshop', 'w')
          ->fields('w', array('pincode'))
          ->condition('type','conference')
          ->condition('foss_name',$name)
          ->condition('state',$state)
          ->execute()
          ->fetchAll();
        // Assigning to each states
        foreach ($query1 as $s) {
          $district = db_select('ai_pincode','a')
            ->fields('a', array('districtname'))
            ->condition('pincode',$s->pincode)
            ->execute()
            ->fetchField();
          $districts[$district]++;
        }
      }
      // Text Book companion
      db_set_active($name);
      if($query->tbc){

        if ($name != 'Python') {
          $query2 = db_query("SELECT po.pincode AS pin FROM {textbook_companion_preference} pe LEFT JOIN {textbook_companion_proposal} po ON pe.proposal_id = po.id WHERE pe.approval_status =1 AND pe.category>0 AND po.state LIKE :state", array(
              ':state' => $state,
          ));
          db_set_active('default');
          while($pin = $query2->fetchObject()->pin) {
            $district = db_select('ai_pincode','a')
              ->fields('a', array('districtname'))
              ->condition('pincode',$pin)
              ->execute()
              ->fetchField();
            $districts[$district]++;
          }
          db_set_active($name);

        }
        else {
            /*$query5 = db_select('tbc_book');
            $query5->addExpression('count(*)', 'count');
            $query5->condition('approved', 1);
            $result5 = $query5->execute();
            $completedbookcount += $result5->fetchObject()->count;
            $query6 = db_select('tbc_book');
            $query6->addExpression('count(*)', 'count');
            $query6->condition('approved', 1, '<>');
            $result6 = $query6->execute();
            $pendingbookcount += $result6->fetchObject()->count;*/
        }
      }
      // Lab Migration
      if($query->lab_migration){
        $query1 = db_select('lab_migration_proposal','u')
          ->fields('u', array('pincode'))
          ->condition('approval_status', 2,'!=')
          ->condition('state',$state)
          ->execute()
          ->fetchAll();
        db_set_active('default');
        foreach ($query1 as $s) {
          $district = db_select('ai_pincode','a')
            ->fields('a', array('districtname'))
            ->condition('pincode',$s->pincode)
            ->execute()
            ->fetchField();
          $districts[$district]++;
        }
        db_set_active($name);
      }
      /*
      //  Self Workshop space
      if($query->foss_selfworkshop_no){
        db_set_active('selfworkshop');
        foreach ($key as $k) {
          $query2 = db_query("SELECT count(t.id) as count FROM {events_training} t, {events_academiccenter} ac, {events_city} c, {events_state} s WHERE t.academic_id=ac.id and ac.city_id=c.id and c.state_id=s.id and (t.status = 4 AND t.foss_id = :foss_id ) and s.name LIKE :state ", array(
            ':foss_id' => $query->foss_selfworkshop_no,
            ':state'=>$k
          ));
          $states[$k] += $query2->fetchObject()->count;
        }

      }
      */
      /* DWSIM Flowsheet */
      if($name == 'DWSIM'){
        db_set_active('DWSIM');
        $query1 = db_select('dwsim_flowsheet_proposal','d')
          ->fields('d', array('pincode'))
          ->condition('approval_status', 2,'!=')
          ->condition('state',$state)
          ->execute()
          ->fetchAll();
        db_set_active('default');
        foreach ($query1 as $s) {
          $district = db_select('ai_pincode','a')
            ->fields('a', array('districtname'))
            ->condition('pincode',$s->pincode)
            ->execute()
            ->fetchField();
          $districts[$district]++;
        }
        db_set_active($name);
      /*  eSim Circuit Simulation */
      }else if($name == 'eSim'){
        db_set_active('eSim');
        $query1 = db_select('esim_circuit_simulation_proposal','e')
          ->fields('e', array('pincode'))
          ->condition('approval_status', 2,'!=')
          ->condition('state',$state)
          ->execute()
          ->fetchAll();
        db_set_active('default');
        foreach ($query1 as $s) {
          $district = db_select('ai_pincode','a')
            ->fields('a', array('districtname'))
            ->condition('pincode',$s->pincode)
            ->execute()
            ->fetchField();
          $districts[$district]++;
        }
        db_set_active($name);

      }

      db_set_active('default');
      db_set_active();
    }

  }
  $i =0;
  //print_r($districts);
  // Findiing Maximum and Total Value from states
  $max = max($districts);
  $total = array_sum($districts);
  /* Dynamic representation of data and Assigning color to each state according to it's value */
  if ($max > 100) {
    $max = $max-($max%100);
    foreach ($districts as $s) {
      if($s > $max){
        $districts[$key[$i]]='#ea5507';
      }else if ($s<=$max && $s>$max*(3/4)) {
        $districts[$key[$i]]='#e56b2b';
      }else if ($s<=$max*(3/4) && $s>$max*(2/4)) {
        $districts[$key[$i]]='#e08859';
      }else if ($s<=$max*(2/4) && $s>$max*(1/4)) {
        $districts[$key[$i]]='#e29d78';
      }else if ($s<=$max*(1/4) && $s>0) {
        $districts[$key[$i]]='#e0ab8f';
      }else{
        $districts[$key[$i]]='#ddc6ba';
      }
      $i++;
    }
  }elseif ($max > 10) {
    $max = $max-($max%10);
    foreach ($districts as $s) {
      if($s > $max){
        $districts[$key[$i]]='#ea5507';
      }else if ($s<=$max && $s>$max/2) {
        $districts[$key[$i]]='#e08859';
      }else if ($s<=$max/2 && $s>0) {
        $districts[$key[$i]]='#e0ab8f';
      }else{
        $districts[$key[$i]]='#ddc6ba';
      }
      $i++;
    }
  }else{
    foreach ($districts as $s) {
      if($s > $max/2){
        $districts[$key[$i]]='#ea5507';
      }else if ($s<=$max/2 && $s>0) {
        $districts[$key[$i]]='#e08859';
      }else{
        $districts[$key[$i]]='#ddc6ba';
      }
      $i++;
    }
  }
  // Setting the data set to generate the map with corresponding colors
  require_once('states/generator.inc');
  $out = generator($districts,$max,$total,$state);
  return $out;

}

 ?>
