<?php
  
class Gestion_BD
{

    var $servidor_mysql="localhost";    // direccion del servidor Mysql, normalmente es "localhost"
    var $usuario="root";         // usuario del servidor Mysql
    var $password;      // password del servidor Mysql
    var $bbdd="ventanas_development";        // nombre de la base de datos
    var $consulta;      // aquí debes meter la consulta Mysql
    var $separador;   /* si vas a usar el mdo result_par_valor_split(),
                                puedes asignar como separar los strings.
                                Por defecto se separan con "#"*/
    var $testeando;   // true o false
    var $email_admin;      /* si "$testeando" es false, entonces pon
                                el email del admin aqui para que reciba
                                notificaciones por email de los errores mysql */
    var $resXML;            // para almacenar el resultado de la query en formato XML
 
    //////////////////////////
    // PROPIEDADES PRIVADAS //
    //////////////////////////
    
    var $conexion;
    var $selec_bbdd="ventanas_development";
    var $string_sucio;
    var $string_limpio;
    var $resultado;
    var $par_valor;
    var $par_valor_split;
    var $par_valor_indx;
    var $largo_separador;
    var $indice;
    var $valor;
    var $n_filas;
    var $n_columnas;
    var $fila;
    var $arr_asoc;
    
    
    /////////////////////////////
    // CONSTRUCTOR DE LA CLASE //
    /////////////////////////////
    
    function ConsultaMysql ()
    {
        $this->separador = "#";
    }
    
    //////////////////////
    // MÉTODOS PRIVADOS //
    //////////////////////
    
    function err ()
    {
        if ($this-> testeando )
        {
            echo "<b><font color='red'>ERROR:</b> --> </b>" .
            mysql_errno ()."</b> - <i>" .mysql_error ()."</i></font>";
            exit ();
        } 
        else
        {
            echo "<b><font color='red'>Ha habido un error</font></b>";
            if ($this-> email_admin )
            {
                echo ", el administrador ha sido informado por email";
                mail ($this-> email_admin ,
                "Error mysql en" .$_SERVER ['PHP_SELF'] ,
                "Error-> " .mysql_error ().
                "\n en->" .$_SERVER ['PHP_SELF'].$_SERVER ['QUERY_STRING'].
                "\n a las-> " .date ('H:i:s - D-d-m-Y'));
            }
            exit ();
        }
    }
    
    //////////////////////
    // MÉTODOS PÚBLICOS //
    //////////////////////
    
    function conectar ()
    {
        // conecta a la bbdd
        $this-> conexion = @mysql_connect ($this-> servidor_mysql , $this-> usuario , $this-> password ) or $this-> err ();
        $this-> selec_bbdd = @mysql_select_db ($this-> bbdd , $this-> conexion ) or $this-> err ();
        return $this->conexion;
    }
    
    function escapar_chars ()
    {
        // añade contrabarras a las palabras que lleven ' " \
        $this-> string_limpio = addslashes ($this-> string_sucio );
        return ($this-> string_limpio );
    }
    function desescapar_chars ()
    {
        // quita las contrabarras para mostrar el texto original con ' " \
        $this-> string_limpio = stripslashes ($this-> string_sucio );
        return ($this-> string_limpio );
    }
    function ejecutar_consulta ()
    {
        // ejecuta consulta Mysql
        $this-> resultado = @mysql_query ($this-> consulta , $this-> conexion ) or $this-> err ($this-> resultado ) or $this-> err ();
        return ($this-> resultado );
    }
    function result_num_filas ()
    {
        // devuelve el numero total de filas (horizontal) de la consulta
        $this-> n_filas = mysql_num_rows ($this-> resultado );
        return $this-> n_filas;
    }
    function result_num_columnas ()
    {
        // devuelve el numero total de columnas (vertical) de la consulta
        $this-> n_columnas = mysql_num_fields ($this-> resultado );
        return $this-> n_columnas;
    }
    function result_array_asoc ()
    {
        // devuelve un array asociativo de la consulta (por nombres de campo envez de por indice de campo)
        while ($this-> fila = mysql_fetch_assoc ($this-> resultado ))
        {
            $this-> arr_asoc [] = $this-> fila;
        }
        return ($this-> arr_asoc );
    }
    function result_par_valor_split ()
    {
        // devuelve una cadena "var0=valor1,valor2,valor3&var1=valor1,valor2,valor3&var2= etc..." con los resultados de la consulta
        $this-> result_array_asoc ();
        $this-> par_valor = array ();
        $this-> largo_separador = strlen ($this-> separador );
        for ($k = 0; $k <sizeof ($this-> arr_asoc ); $k ++)
        {
            while ($this-> valor = current ($this-> arr_asoc [$k]) and $this-> indice = key (($this-> arr_asoc [$k])))
            {
                if ( ! array_key_exists ($this-> indice , $this-> par_valor ))
                {
                    $this-> par_valor [$this-> indice] = "";
                }
                $this-> par_valor [$this-> indice] .= $this-> valor .$this-> separador;
                next ($this-> arr_asoc [$k]);
            }
        }
        foreach ($this-> par_valor as $indice => $valor )
        {
            $this-> par_valor_split .= $indice ."=" .$valor;
            $this-> par_valor_split = substr ($this-> par_valor_split , 0, (strlen ($this-> par_valor_split ) - $this-> largo_separador ));
            $this-> par_valor_split .= "&";
        }
        $this-> par_valor_split = substr ($this-> par_valor_split , 0, (strlen ($this-> par_valor_split ) - 1));
        return (utf8_encode ($this-> par_valor_split));
    }
    
 
    //////////////////////////////////////
    //                  //
    //    método por Marcos Gonzalez   //
    //    http://www.q-interactiva.com  //
    //                  //
    //////////////////////////////////////
    function result_par_valor_indx ()
    {
        /*
        RECIBE: 
        no recibe ningun parámetro ya que todos los que necesita los puede obtener
        de la propia clase.
        
        DEVUELVE: 
        Devuelve en la propiedad par_valor la respuesta a la consulta en formato
        pares de variables valores indexados. Siempre a esta serie de parejas variable
        valor indexadas, les precede una variable llamada n_datos que contiene el numero
        de resultados obtenidos.
        
        DESCRIPCION: 
        Obtiene en el numero de filas el numero de resultados obtenidos en la
        consulta, y a su vez obtiene en el numero de columnas el numero de campos de los
        resultados obtenidos. Posteriormente por cada respuesta (fila) concatena la cadena de
        respuesta con un nuevo grupo de pares variable - valor indexadas con el indice de fila
        del resultado.
        */
        $this-> result_num_filas ();
        $this-> result_num_columnas ();
        $this-> par_valor_indx = "n_datos=" .$this-> n_filas ."&";
        $fil = $this-> result_array_asoc ($this-> resultado );
        for ($i = 0 ; $i <$this-> n_filas ; $i ++)
        {
            foreach ($fil [$i] as $indice => $valor )
            {
                $this-> par_valor_indx .= $indice ."_" .$i ."=" .$valor ."&";
            }
        }
        $this-> par_valor_indx = substr ($this-> par_valor_indx , 0, (strlen ($this-> par_valor_indx ) - 1 ));
        return (utf8_encode ($this-> par_valor_indx));
    }
 
 
    //////////////////////////////////////
    //                  //
    //    método por Marcos Gonzalez   //
    //    http://www.q-interactiva.com  //
    //                  //
    //////////////////////////////////////
    function result_XML()
    {
    /*
    RECIBE: no recibe ningun parámetro ya que todos los que necesita los puede obtener
    de la propia clase.

    DEVUELVE: Devuelve en la propiedad resXML la respuesta a la consulta en formato
    XML. 

    DESCRIPCION: Obtiene en el numero de filas el numero de resultados obtenidos en la
    consulta, y a su vez obtiene en el numero de columnas el numero de campos de los
    resultados obtenidos. Posteriormente por cada respuesta (fila) crea un nodo con sus
    nodos anidados.
    */
        $this->result_num_filas();
        $this->result_num_columnas();
        
        $this->resXML = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<datos>\n";
        
        $fil = $this->result_array_asoc ( $this->resultado );
        
        for ( $i=0 ; $i<$this->n_filas ; $i++ )
        {
                $this->resXML .= "\t<dato>\n";
                foreach ( $fil[$i] as $indice=>$valor )
                {
                         $this->resXML .= "\t\t<".$indice.">".$valor."</".$indice.">\n";
                        
                }
                $this->resXML .= "\t</dato>\n";
        }
 
        $this->resXML.="</datos>";
        return (utf8_encode($this->resXML));  
    }
 
 
 
    function cerrar_conexion ()
    {
        // cierra la conexion existente
        mysql_close ($this-> conexion );
    }
    function info ()
    {
        // devuelve informacion de los campos de la tabla en la cosulta dada de forma grafica,
        // la versión del server mysql y otros datos que pueden interesar acerca del estado del serviddor mysql
        $this-> i = 0;
        $this-> n_columnas = $this-> result_num_columnas ();
        echo "<table cellpadding=3 border=1><tr>";
        while ($this-> i <$this-> n_columnas )
        {
            echo"<td style='font-type:Arial;font-size:14px;'>" .
            "<b style='color:green;'>nombre</b> " .mysql_field_name ($this-> resultado , $this-> i )."<br />" .
            "<b style='color:green;'>tipo</b> " .mysql_field_type ($this-> resultado , $this-> i )."<br />" .
            "<b style='color:green;'>longitud max</b> " .mysql_field_len ($this-> resultado , $this-> i )."<br />" .
            "<b style='color:green;'>flags</b> " .mysql_field_flags ($this-> resultado , $this-> i )."<br />" .
            "</td>";
            $this-> i ++;
        }
        echo "</tr><tr><td colspan=" .$this-> i ." style='font-type:Arial;font-size:14px;'>";
        echo "<b style='color:green;'>La informaciel server es la siguiente:</b><br />" .
        "MySQL server version: " .mysql_get_server_info ();
        echo "<br /><pre>";
        print_r (explode ('  ' , mysql_stat ()));
        echo "</pre>";
        echo "</tr></table>";
    }
} // fin de la clase
 
?> 
