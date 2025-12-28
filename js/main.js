// Main JavaScript for ECURAICES WEBCAMS

document.addEventListener('DOMContentLoaded', function() {
    // Smooth scroll para enlaces internos
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function (e) {
            e.preventDefault();
            const target = document.querySelector(this.getAttribute('href'));
            if (target) {
                target.scrollIntoView({
                    behavior: 'smooth',
                    block: 'start'
                });
            }
        });
    });

    // Manejo de parámetros de URL para categorías
    const urlParams = new URLSearchParams(window.location.search);
    const categoria = urlParams.get('cat');
    
    if (categoria) {
        scrollToCategoria(categoria);
    }

    // Animaciones al hacer scroll
    const observerOptions = {
        threshold: 0.1,
        rootMargin: '0px 0px -50px 0px'
    };

    const observer = new IntersectionObserver(function(entries) {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                entry.target.style.opacity = '1';
                entry.target.style.transform = 'translateY(0)';
            }
        });
    }, observerOptions);

    // Observar elementos con animación
    document.querySelectorAll('.categoria-card, .camara-card').forEach(el => {
        el.style.opacity = '0';
        el.style.transform = 'translateY(20px)';
        el.style.transition = 'opacity 0.6s ease, transform 0.6s ease';
        observer.observe(el);
    });

    // Actualizar hora en tiempo real (si es necesario)
    updateTime();
    setInterval(updateTime, 60000); // Actualizar cada minuto

    // Detectar error en video de YouTube
    checkYouTubeVideo();
});

function scrollToCategoria(categoria) {
    const categoriaElement = document.querySelector(`[data-categoria="${categoria}"]`);
    if (categoriaElement) {
        setTimeout(() => {
            categoriaElement.scrollIntoView({
                behavior: 'smooth',
                block: 'center'
            });
            // Resaltar la categoría
            categoriaElement.style.border = '3px solid #eaab2b';
            categoriaElement.style.boxShadow = '0 8px 30px rgba(234, 171, 43, 0.3)';
            setTimeout(() => {
                categoriaElement.style.border = '';
                categoriaElement.style.boxShadow = '';
            }, 2000);
        }, 300);
    }
}

function updateTime() {
    const timeElements = document.querySelectorAll('.current-time');
    const now = new Date();
    const timeString = now.toLocaleTimeString('es-EC', {
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit'
    });
    timeElements.forEach(el => {
        el.textContent = timeString;
    });
}

// Función para compartir
function shareCamera(url, title) {
    if (navigator.share) {
        navigator.share({
            title: title,
            text: 'Mira esta cámara en vivo en ECURAICES WEBCAMS',
            url: url
        }).catch(err => console.log('Error al compartir:', err));
    } else {
        // Fallback: copiar al portapapeles
        navigator.clipboard.writeText(url).then(() => {
            alert('Enlace copiado al portapapeles');
        });
    }
}

// Función para verificar si el video de YouTube carga correctamente
function checkYouTubeVideo() {
    const videoIframe = document.getElementById('youtube-video-embed');
    const fallback = document.getElementById('video-fallback');
    
    if (!videoIframe || !fallback) return;
    
    // Intentar detectar errores después de que el iframe cargue
    videoIframe.addEventListener('load', function() {
        // Esperar un momento para ver si aparece el error
        setTimeout(() => {
            try {
                // Intentar acceder al contenido del iframe (puede fallar por CORS)
                const iframeDoc = videoIframe.contentDocument || videoIframe.contentWindow.document;
                // Si llegamos aquí, el iframe cargó pero puede tener error
            } catch (e) {
                // CORS bloquea el acceso, pero esto es normal
                // El error 153 se mostrará dentro del iframe
            }
        }, 2000);
    });
    
    // Si el iframe no carga después de 5 segundos, mostrar fallback
    setTimeout(() => {
        // Verificar si el iframe tiene contenido visible
        // Nota: No podemos verificar directamente por CORS, pero podemos
        // mostrar el fallback si el usuario hace clic y no funciona
    }, 5000);
}

// Exportar funciones para uso en otros archivos
window.ECURAICES = {
    shareCamera: shareCamera,
    scrollToCategoria: scrollToCategoria
};


