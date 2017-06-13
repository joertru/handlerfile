<?php

/**
 * This field handler displays a node's nid with custom text.
 *
 * @ingroup views_field_handlers
 */
class handlerfile_handler_file extends views_handler_field_entity {
  
  function option_definition() {
    $options = parent::option_definition();
    $options['field_file']  = array('default' => '');
    $options['field_delta'] = array('default' => 0);
    $options['img_styles']  = array('default' => '');
    return $options;
  }
  
    /**
   * Creates the form item for the options added.
   */
  function options_form(&$form, &$form_state) 
  {
    parent::options_form($form, $form_state);
    
    $img_styles =image_styles();
    foreach($img_styles as $key => $style){
      $options[$key] = $style['label'];
    }
    
    $query  = db_select('field_config', 'fg')->fields('fg', array('id', 'field_name', 'data'))->condition('fg.type', 'file' );
    $results = $query->execute();
    $rfetch = $results->fetchAll();
    $num_of_results = $results->rowCount();
    if( $num_of_results > 0)
    {
       foreach($rfetch as $rfield ){
         $fields[$rfield->field_name] = $rfield->field_name;
       }
    }
  
    $form['field_file'] = array(
      '#type' => 'select',
      '#title' => t('Campo File a renderizar'),  
      '#default_value' => $this->options['field_file'],
      '#options'=> $fields,
      '#required' => TRUE
    );
    
    $form['field_delta'] = array(
      '#type' => 'select',
      '#title' => t('Delta'),  
      '#default_value' => $this->options['field_delta'],
      '#options'=> array(0,1,2,3,4,5,6,7,8,9),
      '#required' => TRUE
    );
    
    $form['img_styles'] = array(
      '#type' => 'select',
      '#title' => t('Estilos de imagen'),
      '#default_value' => $this->options['img_styles'],
      '#options'=> $options,
      '#required' => TRUE
    );
  }
  
  /**
   * Renders the field handler.
   */
  function render($values) {
    $campo = 'field_'.$this->options['field_file'];
    $delta = $this->options['field_delta'];
    $fid = $values->{$campo}[$delta]['raw']['fid'];
    $uri = $values->{$campo}[$delta]['raw']['uri'];
    $img = image_style_url($this->options['img_styles'], $uri);
    return format_string('<img src="@img" class="img-responsive" />', array('@img' => $img ));
  }
  
}

?>