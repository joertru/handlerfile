<?php

/**
 * Implements hook_views_data_alter().
 */
function handlerfile_views_data_alter(&$data) {
  $data['node']['sfile'] = array(
    'title' => 'HandlerFile',
    'help' => 'Field Render custom field file',
    'field' => array(
      'handler' => 'handlerfile_handler_file',
    ),
  );
}

?>