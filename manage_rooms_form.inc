<?php

/**
 * This file contains the forms for managing the room settings.
 * The settings are used to compute the total available spots for
 * each type of room registration.
 *
 * Rooms assigned by the facility can vary per event so there is 
 * provisions for keeping a master list of rooms and their configurations
 * in nodes (MC Room).  The rooms can then be marked as available or not.
 * Also, the facility may ask that one floor be filled before the other, so
 * rooms can be marked as assignable or not.  And lastly, the double rooms
 * can be assigned to a single person which means its treated as a single room
 * in all room counts and what the registrant is charged, etc.
 *
 * There is a reset button on the instructions page to reset the 2 floor variables
 * to the settings in the MC Room nodes.
 */

require_once("retreatform_defines.inc");
require_once("retreatform_utilities.inc");

function form_manage_rooms() {
  return t('Just a place holder...');
}

/*
 * Instructions Page
 *
 * This page will have instructions plus a reset button used to
 * reset the rooms variables to the "template" stored in the MC
 * Rooms nodes, which have all possible rooms at normal bed counts.
 * The reset is to be used when a new retreat event is created or
 * the facility changes the rooms we get for the retreat.
 */
function form_manage_setup_init($form, &$form_state) {

  $form['available_text'] = array(
    '#markup' => t('</br><h2 style="text-align: left;">How to use the Available checkbox</h2><p style="text-align: left;">This checkbox is used to mark a room available.  When Mercy Center assigns rooms for a retreat, you check the Available checkbox to make that room available to the retreat.  Once these selections are saved the ones that were not checked will not show up.  If the available rooms change or a new retreat is being planned, use the reset feature explained below.</p></br>'),
  );

  $form['assignable_text'] = array(
    '#markup' => t('<h2 style="text-align: left;">How to use the Assignable checkbox</h2><p style="text-align: left;">This checkbox is used to mark rooms as not being assignable yet.  Such as if Mercy Center requests that the second floor rooms are filled first.  Or another point of view, checking this box adds the room to the available count on the registration form.  These rooms will always appear in the listing.</p></br>'),
  );

  $form['beds_count_update'] = array(
    '#markup' => t('<h2 style="text-align: left;">Updating the Bed Count</h2><p style="text-align: left;">This one is pretty straight forward.  If the room has 2 beds but only one will be used, change the count to 1.  It will then be counted as an option 1 private room.</p></br>'),
  );

  $form['reset_rooms_text'] = array(
    '#markup' => t('<h2 style="text-align: left;">Reset Room Settings</h2><p style="text-align: left;">This button should only be used when a new retreat is being planned or when the rooms available have been changed by Mercy Center.  The result of using this button is that all room settings will be reset and will need to be re-done.</p></br>'),
  );

  $form['reset_rooms_button'] = array(
    '#prefix' => '<div class="registration-submit">',  // used so don't have to change CSS
    '#suffix' => '</div>',
    '#type' => 'submit',
    '#value' => t('<< RESET ROOMS >>'),
    '#title' => t('This will reset all room settings!!'),
    '#submit' => array('form_manage_rooms_reset_submit'),
  );

  return $form;  
}

/*
 * First floor form
 */
function form_manage_first_floor_rooms($form, &$form_state) {

  // Setup first floor array from initialized variable
  $first_floor_rooms = variable_get('first_floor_rooms');
  
  $form['description_page1'] = array(
    '#type' => 'item',
    '#title' => t('First Floor Rooms'),
  );
  
  // Generate this floor form items
  generate_floor_form($form, $form_state, $first_floor_rooms);

  $form['submit_1st_floor_rooms'] = array(
    '#prefix' => '<div class="registration-submit">',  // used so don't have to change CSS
    '#suffix' => '</div>',
    '#type' => 'submit',
    '#value' => t('<< Update First Floor Rooms >>'),
    '#submit' => array('form_manage_rooms_first_floor_submit'),
  );

  return $form;  
}

/*
 * Second floor form
 */
function form_manage_second_floor_rooms($form, &$form_state) {

  // Setup first floor array from initialized variable
  $second_floor_rooms = variable_get('second_floor_rooms');

  $form['description_page2'] = array(
    '#type' => 'item',
    '#title' => t('Second Floor Rooms'),
  );

  // Generate this floor form items
  generate_floor_form($form, $form_state, $second_floor_rooms);

  $form['submit_2nd_floor_rooms'] = array(
    '#prefix' => '<div class="registration-submit">',  // used so don't have to change CSS
    '#suffix' => '</div>',
    '#type' => 'submit',
    '#value' => t('<< Update Second Floor Rooms >>'),
    '#submit' => array('form_manage_rooms_second_floor_submit'),
  );

  return $form;  
}

/**
 * Submit handler for the first floor.
 *
 * Save the first floor settings in the MC Room nodes
 */
function form_manage_rooms_first_floor_submit($form, &$form_state) {

  // Get current variable value  
  $first_floor_rooms = variable_get('first_floor_rooms');

  // Save the form state to the first floor variable
  foreach($first_floor_rooms as $key => $value) {
  
    // Only update room if its available
    if ($value['available'] != 0) {
      
      $available = 'available_' . $key;
      $assignable = 'assignable_' . $key;
      $beds = 'beds_' . $key;

      // Update values
      $value['available'] = $form_state['values'][$available];
      $value['assignable'] = $form_state['values'][$assignable];
      $value['number_of_beds'] = $form_state['values'][$beds];
      
      // Save updates
      $first_floor_rooms[$key] = $value;
    }
  }

  // Update the database with the new variable value
  variable_set('first_floor_rooms', $first_floor_rooms);
}

/*
 * Submit handler for the second floor.
 *
 * Save the second floor settings in the MC Room nodes
 */
function form_manage_rooms_second_floor_submit($form, &$form_state) {

  // Get current variable value  
  $second_floor_rooms = variable_get('second_floor_rooms');

  // Save the form state to the second floor variable
  foreach($second_floor_rooms as $key => $value) {
  
    // Only update room if its available
    if ($value['available'] != 0) {
    
      $available = 'available_' . $key;
      $assignable = 'assignable_' . $key;
      $beds = 'beds_' . $key;

      // Update values
      $value['available'] = $form_state['values'][$available];
      $value['assignable'] = $form_state['values'][$assignable];
      $value['number_of_beds'] = $form_state['values'][$beds];
      
      // Save updates
      $second_floor_rooms[$key] = $value;
    }
  }

  // Update the database with the new variable value
  variable_set('second_floor_rooms', $second_floor_rooms);
}

/*
 * This function is called from the instructions page and will
 * reset the floor variables to the values from the MC Room
 * nodes.  Its used to reset the variables for a new retreat or
 * if Mercy Center changes the rooms assigned.
 *
 */
function form_manage_rooms_reset_submit($form, &$form_state) {
  drupal_set_message(t('The room settings have been reset.'));

  // The hook_init fuction in the module file will actually
  // reset the variables  
  variable_set('initialized_1st_floor', FALSE);
  variable_set('initialized_2nd_floor', FALSE);
}

/*
 * This function generates the form items per floor
 *
 */
function generate_floor_form(&$form, $form_state, $rooms) {
  
  // Generate the form elements for each floor
  foreach($rooms as $key => $value) {

    // Only list room if its available
    if ($value['available'] != 0) {

      // Room string
      $option = $value['room_type'];
      $room_description = 'Room ' . $key . '/' . room_str($option);
      if ($value['connecting_room'] != NULL) {
        $room_description = $room_description . '/Connecting Room: ' . $value['connecting_room'];
      }
      if ($value['elevator'] != 0) {
        $room_description = $room_description . '/Elevator';
      }
      if ($value['handicapped'] != 0) {
        $room_description = $room_description . '/Handicapped';
      }
      
      $form[$key] = array(
        '#type' => 'fieldset',
        '#title' => check_plain($room_description),
        '#states' => array('visible' => TRUE),
      );
      
      $available = 'available_' . $key;
      $assignable = 'assignable_' . $key;
      $beds = 'beds_' . $key;
    
      $form[$key][$available] = array(
        '#type' => 'checkbox',
        '#title' => t('Available?'),
        '#prefix' => '<div style="float: left; margin-right: 20px;">',
        '#suffix' => '</div>',
        //'#required' => TRUE,
        '#default_value' => !empty($form_state['values'][$available]) ? t($form_state['values'][$available]) : $value['available'],
      );

      $form[$key][$assignable] = array(
        '#type' => 'checkbox',
        '#title' => t('Assignable?'),
        '#prefix' => '<div style="float: left; margin-right: 20px;">',
        '#suffix' => '</div>',
        //'#required' => TRUE,
        '#default_value' => !empty($form_state['values'][$assignable]) ? t($form_state['values'][$assignable]) : $value['assignable'],
      );
    
      if ($option == 'OPTION_3') {
        $form[$key][$beds] = array(
          '#type' => 'select',
          '#title' => t('Number of Beds'),
          '#description' => t('Select 1 to change to single room'),
          '#options' => array('1' => 1, '2' => 2),
          '#prefix' => '<div style="float: left;">',
          '#suffix' => '</div>',
          //'#required' => TRUE,
          '#default_value' => !empty($form_state['values'][$beds]) ? t($form_state['values'][$beds]) : $value['number_of_beds'],
        );
      } else {
        $form[$key][$beds] = array(
          '#type' => 'select',
          '#title' => t('Number of Beds'),
          // Can't change the number of beds because there is only 1 for these types of rooms
          '#disabled' => TRUE,
          '#options' => array('1' => 1),
          '#prefix' => '<div style="float: left;">',
          '#suffix' => '</div>',
          //'#required' => TRUE,
          '#default_value' => 1,
        );
      }
    }
  }
}