<?php
session_start();
date_default_timezone_set('Europe/Madrid');

require('manager/Camara.inc');
require('manager/Usuario.inc');
require('manager/Concejo.inc');
require('manager/Comentario.inc');

$gestion_usuarios = new Usuario(); 
$gestion_camaras = new Camara();
$gestion_concejos = new Concejo();
$gestion_comentarios = new Comentario();

if(isset($_GET["id"]) && (is_numeric($_GET["id"]))) {
    $id = $_GET["id"];
} else {
    $id = 1;
}

switch ($id) {
    case 1:
        $listado_cams = "En instalación";
        $listado_cams_breadcrumb = "en instalación";
        $cadbusca = "SELECT * FROM camara WHERE activada=2";
        break;
    case 2:
        $listado_cams = "HD";
        $listado_cams_breadcrumb = "HD";
        $cadbusca = "SELECT * FROM camara WHERE activada=1 AND hd=1";
        break;
    case 3:
        $listado_cams = "En mantenimiento";
        $listado_cams_breadcrumb = "en mantenimiento";
        $cadbusca = "SELECT * FROM camara WHERE activada=1 AND estado=-1";
        break;
    case 4:
        $listado_cams = "Pendientes de mejora";
        $listado_cams_breadcrumb = "pendientes de mejora";
        $cadbusca = "SELECT * FROM camara WHERE mejora=1";
        break;
}

// Update database connection to use environment variables
$db_host = 'localhost';  // Docker service name
$db_user = 'webcamsd_webcams';
$db_pass = '17101982';
$db_name = 'ventanas_development';  // This should match MYSQL_DATABASE in docker-compose.yml

error_log("Attempting to connect to database: host=$db_host, user=$db_user, db=$db_name");

$v = mysqli_connect($db_host, $db_user, $db_pass, $db_name);
if (!$v) {
    error_log("Error de conexión: " . mysqli_connect_error());
    // Instead of dying, set default values
    $num = 0;
    $cameras = array();
} else {
    mysqli_set_charset($v, 'utf8');

    $resultado = mysqli_query($v, $cadbusca);
    $num = 0;
    if($resultado) {
        $num = mysqli_num_rows($resultado);
        error_log("Consulta exitosa. Número de resultados: " . $num);
    } else {
        error_log("Error en la consulta: " . mysqli_error($v));
    }

    // Get cameras data
    $cameras = array();
    if ($resultado && $num > 0) {
        error_log("Iniciando carga de cámaras. Número esperado: " . $num);
        
        // Debug: Ver estructura de la primera fila
        $first_row = mysqli_fetch_assoc($resultado);
        error_log("Estructura de la primera fila: " . print_r($first_row, true));
        
        // Resetear el puntero del resultado
        mysqli_data_seek($resultado, 0);
        
        while ($row = mysqli_fetch_assoc($resultado)) {
            error_log("Procesando fila: " . print_r($row, true));
            
            // Verificar que los campos necesarios existen
            $required_fields = ['id', 'nombre'];
            $missing_fields = array_diff($required_fields, array_keys($row));
            
            if (!empty($missing_fields)) {
                error_log("Faltan campos requeridos: " . implode(', ', $missing_fields));
                continue;
            }
            
            try {
                $camera_data = array(
                    'id' => $row['id'],
                    'nombre' => $row['nombre'],
                    'pueblo' => isset($row['pueblo']) ? $row['pueblo'] : '',
                    'descripcion' => isset($row['descripcion']) ? $row['descripcion'] : '',
                    'imagen' => isset($row['imagen']) ? $row['imagen'] : '',
                    'valoracion' => isset($row['valoracion']) ? $row['valoracion'] : 0,
                    'patrocinadores' => isset($row['patrocinadores']) ? $row['patrocinadores'] : ''
                );
                
                error_log("Datos de cámara procesados: " . print_r($camera_data, true));
                $cameras[] = $camera_data;
                
            } catch (Exception $e) {
                error_log("Error al procesar cámara: " . $e->getMessage());
                continue;
            }
        }
        
        error_log("Total de cámaras cargadas: " . count($cameras));
        error_log("Estructura final de cameras: " . print_r($cameras, true));
    } else {
        error_log("No hay resultados para procesar. num=$num, resultado=" . ($resultado ? 'true' : 'false'));
    }

    mysqli_close($v);
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xml:lang="es" lang="es" xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>Webcams de Asturias - El tiempo en Asturias en directo desde nuestras cámaras</title>
    <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
    <META NAME="Author" CONTENT="Red de Webcams Asturias en España desde Asturias">
    <META NAME="Subject" CONTENT="Webcams de Asturias en España - Cámaras IP en Asturías">
    <META NAME="Description" CONTENT="Webcams de España desde Asturias es la red de webcams de promoción turística del Principado de Asturias. Asturias en directo las 24 horas del día">
    <META NAME="Keywords" CONTENT="España, Spain, Webcam. Cámara IP, Turismo. Meteorología, Asturias, Costa, Playas, Montaña, Tiempo, Oviedo, Gijón">
    <META NAME="Language" CONTENT="Spanish">
    <META NAME="Distribution" CONTENT="Global">
    <META NAME="Robots" CONTENT="All">
    <link rel="icon" href="https://www.webcamsdeasturias.com/favicon.ico" type="image/x-icon" />
    <meta http-equiv="X-UA-Compatible" content="IE=8" />
    <link rel='stylesheet' href='/infoasturias/Estilos/hojaEstilos.css' type='text/css'>
    <link type="text/css" rel="stylesheet" href="/css/general.css" media="all" />
    <link type="text/css" rel="stylesheet" href="/css/bootstrap.css" media="all">
    <script type="text/javascript" src="http://webcamsdeasturias.com/js/cookie.js"></script>
</head>
<body>
    <div id="contenedor">
        <div id="centrado">
            <?php if(!isset($_SESSION["nick"])){ 
                $array = array("www.jairecanoas.com","www.villademestas.com");
                $alts = array("Descenso del Sella","Alojamiento en Asturias");
                $ids = array(8,13);
                $aux = rand(0,1);
            ?>
            <a class="gestionPublicidad" data-url="<?php echo "https://".$array[$aux]; ?>" data-id="<?php echo $ids[$aux]; ?>" data-pos="1" href="https://<?php echo $array[$aux]; ?>">
                <img border="0" src="/banners/h_<?php echo $aux?>.jpg" title="<?php echo $alts[$aux] ?>" alt="<?php echo $alts[$aux] ?>" width="975px" style="padding:0px; margin:0px;"/>
            </a>
            <?php }; ?> 

            <?php include "./nuevacabecera_auxiliar.php"; ?>

            <div id="contenido2">
                <span>
                    <ul class="breadcrumb">
                        <li><a href="https://www.webcamsdeasturias.com">Inicio</a> <span class="divider"> | </span></li>
                        <li class="active"> Listado de cams <?php echo $listado_cams_breadcrumb; ?></li>
                    </ul>
                </span>

                <h1>Listado de cámaras: <?php echo htmlspecialchars($listado_cams); ?> (<?php echo $num; ?>)</h1>

                <div class="salto"></div>
                <br/>

                <?php 
                if (empty($cameras)) {
                    echo "<p><strong>No se han encontrado cámaras en esta categoría.</strong></p>";
                } else {
                    if (!isset($_SESSION["nick"])) {
                        ?>
                        <div class="alert alert-info">
                            <p><strong>¿Quieres ver las imágenes en tiempo real?</strong> 
                               <a href="https://www.webcamsdeasturias.com/alta-socios-webcams.html">
                                   <strong>Hazte socio de Webcams de Asturias</strong>
                               </a> y tendrás acceso a todas las cámaras en directo.
                            </p>
                        </div>
                        <?php
                    }
                    ?>
                    <div id='mosaicoMiniCam' style='margin-left:-15px !important'>
                        <table>
                            <?php foreach($cameras as $camera): ?>
                                <tr>
                                    <?php if(isset($_SESSION["nick"])): ?>
                                    <td width="175px" height="150px">
                                        <div class="miniCam">
                                            <div class="imagen">
                                                <div style="width:8.8em;height:6.5em;">
                                                    <a href="/camara/<?php echo $camera['id']; ?>" 
                                                       title="<?php echo htmlspecialchars($camera['nombre']); ?>">
                                                        <?php if($id != 1): ?>
                                                            <img src="<?php echo htmlspecialchars($camera['imagen']); ?>" 
                                                                 alt="<?php echo htmlspecialchars($camera['nombre']); ?>"/>
                                                        <?php else: ?>
                                                            <img src="https://www.webcamsdeasturias.com/imagenes/eninstalacion.jpg" 
                                                                 alt="En instalación"/>
                                                        <?php endif; ?>
                                                    </a>
                                                </div>
                                            </div>
                                        </div>
                                    </td>
                                    <?php endif; ?>
                                    <td>
                                        <a class="enlace" style="font-size:14px;" 
                                           href="/camara/<?php echo $camera['id']; ?>" 
                                           title="<?php echo htmlspecialchars($camera['nombre']); ?>">
                                            <strong>
                                                <?php echo htmlspecialchars($camera['nombre']); ?>
                                            </strong>
                                        </a>
                                    </td>
                                </tr>
                            <?php endforeach; ?>
                        </table>
                    </div>
                    <?php
                }
                ?>

                <?php if (!isset($_SESSION["nick"])){ ?>
                <p align="center">
                <script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
                <ins class="adsbygoogle"
                     style="display:inline-block;width:700px;height:100px"
                     data-ad-client="ca-pub-9312774265223578"
                        $listado_cams_breadcrumb="en instalación";
                     data-ad-slot="6992727350"></ins>
                <script>
                (adsbygoogle = window.adsbygoogle || []).push({});
                </script>
                </p>
                <?php } ?>

                <div class="salto"></div>
                </br>
               

                <p>
                Si deseas instalar una cam en tu localidad, conocer el estado de alguno de los equipos, saber las tarifas publicitarias... no dudes en contactar con nosotros en la <a href="https://webcamsdeasturias.com/contacto.php"><b>zona de contacto</b></a> y estaremos encantados de atender tu consulta.
                </p>

                <div class="salto"></div>

                 <div class="hero-unit" style="text-align: left; margin-bottom:10px; margin-top:10px;">
                <h2>Top 10 cams del día</h2>

                <?php                  
                        $arrContextOptions=array(
                          "ssl"=>array(
                                "verify_peer"=>false,
                                "verify_peer_name"=>false,
                            ),
                        );  

                $response = file_get_contents('./rankings/top-cams-day.inc', false, stream_context_create($arrContextOptions));

                echo utf8_encode($response);
                        ?>
                </div>					



                <?php if (!isset($_SESSION["nick"])){ ?>

                </br>
                <p align="center">

                <script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>
                <ins class="adsbygoogle"
                     style="display:inline-block;width:700px;height:100px"
                     data-ad-client="ca-pub-9312774265223578"
                     data-ad-slot="6992727350"></ins>
                <script>
                (adsbygoogle = window.adsbygoogle || []).push({});
                </script>

                </p>
                <?php } ?>
                   
                               <div class="salto"></div>
                                 <div class="salto"></div>
                            


                <div class="hero-unit">
                        <h2>Tendencias | Lo más buscado en Webcams de Asturias</h2>
                        <?php                  
                                require('./top.inc'); 
                                ?>
                                </div>

                        <!-- ** ENLACES ** -->
                            
                        <div class="enlaces">
                        
                        </div>
                        
                        <!-- PIE -->
                        <div id="pie">
                           <?php require('./pie.inc'); ?>
                        </div>
                    </div>
                    

                    <!-- ** Columna derecha (registro,noticias,...) ** -->
                    <div id="columnaD2">
                        
                <?php if (!isset($_SESSION["nick"])){ ?>
                         <?php require('./adsense.inc'); ?>
                <?php } ?>   
                
                <div class="noticias">
                
                        <h1>&Uacute;LTIMOS COMENTARIOS</h1>
                        <?php 
                        $comentarios=$gestion_comentarios->getListaComentariosTodos(5);
                        
                        for($i=0;$i<count($comentarios);$i++)
                         {
                        ?>
                        
                        <div>  
                            <h2><a href='<?php echo $gestion_camaras->getUrlFriendly($comentarios[$i]->getCamara()); ?>' title="Ver comentario"><?php echo $gestion_camaras->getCamara($comentarios[$i]->getCamara())->getNombre(); ?></a></h2>
                            <div class="desarrollo">
                                <div class="fecha"><?php echo $comentarios[$i]->getFecha(); ?></div>
                                <div class="ampliar"><p>
                                 <?php 
                                   echo substr($comentarios[$i]->getTexto(),0,100);
                                 ?>

                                  ...<a href="<?php echo $gestion_camaras->getUrlFriendly($comentarios[$i]->getCamara()); ?>">[+]</a>
                                </p>
                               </div>
                             </div>
                        </div>
                        
                        
                        <?php 
                         }
                        ?>

                        
                    </div>
            <br/>
            <?php if (!isset($_SESSION["nick"])){ ?>
                    <script type="text/javascript"><!--
            google_ad_client = "pub-9312774265223578";
            /* 250x250, creado 6/01/10 */
            google_ad_slot = "4498651671";
            google_ad_width = 250;
            google_ad_height = 250;
            //-->
            </script>
            <script type="text/javascript"
            src="//pagead2.googlesyndication.com/pagead/show_ads.js">
            </script>
            <?php } ?>
                    </div>    
                </div>
            </div>
        </div>
    </div>
</body>
</html>
