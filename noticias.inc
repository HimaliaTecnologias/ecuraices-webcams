<?php
// Asegurarnos que no hay salida antes de los headers
ob_start();

function getNoticias() {
    try {
        $gestion_contenidos = new Contenido();
        
        // Llamamos a getListaNoticias con el parámetro requerido
        // Asumimos que el primer parámetro es un límite o un tipo
        $noticias = $gestion_contenidos->getListaNoticias(10); // O cualquier otro valor que necesite
        
        if (!$noticias) {
            //error_log("Error obteniendo las noticias");
            return array();
        }

        return $noticias;

    } catch (Exception $e) {
        error_log("Excepción en getNoticias: " . $e->getMessage());
        return array();
    }
}

function getCategory($category) {
    // Siempre devolvemos "Información General"
    return 'Información General';
}

function urlsAmigables($text) {
    if (!is_string($text)) {
        return 'n-a';
    }

    // Convert to UTF-8 if not already
    $text = mb_convert_encoding($text, 'UTF-8', mb_detect_encoding($text));
    
    // Replace special characters
    $text = str_replace(
        array('á','é','í','ó','ú','ñ','Á','É','Í','Ó','Ú','Ñ'),
        array('a','e','i','o','u','n','A','E','I','O','U','N'),
        $text
    );

    // Replace non-alphanumeric characters with hyphen
    $text = preg_replace('/[^\p{L}\p{N}]+/u', '-', $text);
    
    // Remove unwanted characters
    $text = preg_replace('/[^-\w]+/', '', $text);
    
    // Trim hyphens and convert to lowercase
    $text = trim(strtolower($text), '-');
    
    return $text ?: 'n-a';
}

function mostrarNoticia($contenido, $cont) {
    try {
        $category = getCategory($contenido->getCategoria());
        $link = sprintf(
            "https://www.webcamsdeasturias.com/cms/%s/%s/%d/",
            urlsAmigables($category),
            urlsAmigables($contenido->getTitulo()),
            (int)$contenido->getId()
        );
        
        $title = htmlspecialchars($contenido->getTitulo(), ENT_QUOTES, 'UTF-8');
        $description = htmlspecialchars($contenido->getResumen(), ENT_QUOTES, 'UTF-8');
        $timestamp = date('d-m-Y', strtotime($contenido->getFecha()));
        
        // Debug: ver qué valor tiene la imagen
        $imagen = $contenido->getImagen();
        //error_log("Imagen para noticia " . $contenido->getId() . ": " . print_r($imagen, true));
        ?>
        <div class="noticia" style="padding-left: 0px; width: 100%; box-sizing: border-box;">
            <div style="width: 100%;">
                <span class="tituloNoticia"><?= $category ?></span>
                <a class="vinculoNoticia" style="font-size: 21px;" href="<?= $link ?>" title="Leer más">
                    <?= $title ?>
                </a>
                <span>
                    <p style="margin-top: 2px; color: #868685; font-size: small">
                        <?= $timestamp ?> | Webcams de Asturias
                    </p>
                </span>
                
                <?php 
                // Debug: mostrar información sobre la imagen
                // error_log("Verificando imagen: " . ($imagen ? "tiene valor" : "es null") . 
                //         " - Trim: " . (trim($imagen) !== '' ? "no está vacío" : "está vacío"));
                ?>
                
                <?php if ($imagen && trim($imagen) !== ''): ?>
                <div class="image">
                    <a class="vinculoNoticia" href="<?= $link ?>" title="Leer más">
                        <?php 
                        $imgUrl = "https://www.webcamsdeasturias.com/cms/uploads/" . trim($imagen) . "L.jpg";
                        //error_log("URL de la imagen: " . $imgUrl);
                        ?>
                        <img style="border: 1px solid #54ADDE; width: 100%; max-width: 360px; display: block; margin: 10px 0;" 
                             src="<?= $imgUrl ?>" 
                             alt="<?= $title ?>"
                             onerror="console.log('Error cargando imagen: <?= $imgUrl ?>'); this.style.display='none';"/>
                    </a>
                </div>
                <?php else: ?>
                    <?php //error_log("No se muestra imagen para noticia " . $contenido->getId()); ?>
                <?php endif; ?>

                <span class="resumen"><?= $description ?></span>
            </div>
        </div>
        <?php
    } catch (Exception $e) {
        //error_log("Error mostrando noticia: " . $e->getMessage());
    }
}

// Limpiar cualquier salida pendiente
ob_end_clean();
?>

<div class="noticiasPortada">
    <br/>
    <h2>Noticias de Webcams de Asturias</h2>

    <div style="width: 360px; float: left; margin-right: 10px;">
        <?php
        $noticias = getNoticias();
        $cont = 0;
        foreach ($noticias as $noticia) {
            if ($cont % 2 == 0) {
                mostrarNoticia($noticia, $cont);
            }
            $cont++;
        }
        ?>
    </div>

    <div style="width: 360px; float: left; padding-left: 15px;">
        <?php
        $cont = 0;
        foreach ($noticias as $noticia) {
            if ($cont % 2 != 0) {
                mostrarNoticia($noticia, $cont);
            }
            $cont++;
        }
        ?>
    </div>
</div>
