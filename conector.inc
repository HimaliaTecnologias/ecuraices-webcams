<?php
// Función para realizar la conexión con la base de datos
if (!function_exists('conectar')) {
    function conectar() {
        try {
            // En Docker, usamos el nombre del servicio de la base de datos
            $host = 'localhost';  // Nombre del servicio MySQL/MariaDB en Docker
            $user = 'webcamsd_webcams';
            $pass = '17101982';
            $dbname = 'webcamsd_ventanas';  // Coincide con MYSQL_DATABASE en docker-compose.yml
            
            $servidor = new mysqli($host, $user, $pass, $dbname);
            
            if ($servidor->connect_error) {
                error_log("Error de conexión MySQL: (" . $servidor->connect_errno . ") " . $servidor->connect_error);
                return null;
            }
            
            // Establecer charset utf8
            if (!$servidor->set_charset("utf8")) {
                error_log("Error cargando el conjunto de caracteres utf8: " . $servidor->error);
            }
            
            return $servidor;
            
        } catch (Exception $e) {
            error_log("Excepción en la conexión: " . $e->getMessage());
            return null;
        }
    }
}
?>
