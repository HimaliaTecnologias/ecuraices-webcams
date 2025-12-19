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

// Exportar funciones para uso en otros archivos
window.ECURAICES = {
    shareCamera: shareCamera,
    scrollToCategoria: scrollToCategoria
};


