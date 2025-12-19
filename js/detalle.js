// JavaScript específico para la página de detalle de cámara

document.addEventListener('DOMContentLoaded', function() {
    // Obtener ID de la cámara desde la URL
    const urlParams = new URLSearchParams(window.location.search);
    const camaraId = urlParams.get('id') || '1'; // Por defecto cámara 1

    // Cargar información de la cámara
    loadCamaraInfo(camaraId);

    // Simular carga del video (en producción aquí iría la URL real del stream)
    simulateVideoLoad();
});

function loadCamaraInfo(camaraId) {
    // Datos de las cámaras (en producción esto vendría de una API)
    const camaras = {
        '1': {
            nombre: 'Santa Elena - Playa Ballenita',
            ubicacion: 'Santa Elena, Ecuador',
            descripcion: 'Hermosa playa con vista al océano Pacífico. Disfruta de las olas, la brisa marina y los atardeceres espectaculares.',
            categoria: 'Playa',
            estado: 'Activa',
            calidad: 'HD - Alta definición',
            streamUrl: 'https://rtsp.me/embed/9kbKi9AG/',
            colaborador: {
                nombre: 'Hostería Mirador Farallón Dillon',
                descripcion: 'Disfruta de una experiencia única con vistas espectaculares al océano Pacífico. Hospedaje de calidad en Santa Elena.',
                url: 'https://www.miradorfarallondillon.com',
                mostrar: true
            }
        }
    };

    const camara = camaras[camaraId];
    if (camara) {
        // Actualizar información si es necesario
        console.log('Cámara cargada:', camara);
        
        // Mostrar/ocultar banner del colaborador
        const sponsorBanner = document.getElementById('sponsorBanner');
        if (sponsorBanner && camara.colaborador && camara.colaborador.mostrar) {
            // Actualizar información del colaborador
            const sponsorTitle = sponsorBanner.querySelector('.sponsor-title');
            const sponsorDescription = sponsorBanner.querySelector('.sponsor-description');
            const sponsorLink = sponsorBanner.querySelector('.btn-sponsor');
            
            if (sponsorTitle) sponsorTitle.textContent = camara.colaborador.nombre;
            if (sponsorDescription) sponsorDescription.textContent = camara.colaborador.descripcion;
            if (sponsorLink && camara.colaborador.url) {
                sponsorLink.href = camara.colaborador.url;
            }
            
            sponsorBanner.style.display = 'block';
        } else if (sponsorBanner) {
            sponsorBanner.style.display = 'none';
        }
    }
}

function simulateVideoLoad() {
    // El iframe se carga automáticamente, no necesitamos simular carga
    const videoIframe = document.getElementById('videoIframe');
    if (videoIframe) {
        // El iframe ya está configurado para cargar automáticamente
        console.log('Video stream cargado');
    }
}

function toggleFullscreen() {
    const videoIframe = document.getElementById('videoIframe');
    if (!videoIframe) return;

    if (!document.fullscreenElement) {
        // Intentar pantalla completa del iframe
        if (videoIframe.requestFullscreen) {
            videoIframe.requestFullscreen();
        } else if (videoIframe.webkitRequestFullscreen) {
            videoIframe.webkitRequestFullscreen();
        } else if (videoIframe.msRequestFullscreen) {
            videoIframe.msRequestFullscreen();
        } else {
            // Fallback: pantalla completa del contenedor
            const videoContainer = document.querySelector('.video-wrapper');
            if (videoContainer) {
                if (videoContainer.requestFullscreen) {
                    videoContainer.requestFullscreen();
                } else if (videoContainer.webkitRequestFullscreen) {
                    videoContainer.webkitRequestFullscreen();
                } else if (videoContainer.msRequestFullscreen) {
                    videoContainer.msRequestFullscreen();
                }
            }
        }
    } else {
        if (document.exitFullscreen) {
            document.exitFullscreen();
        } else if (document.webkitExitFullscreen) {
            document.webkitExitFullscreen();
        } else if (document.msExitFullscreen) {
            document.msExitFullscreen();
        }
    }
}

function refreshVideo() {
    const videoIframe = document.getElementById('videoIframe');
    
    if (videoIframe) {
        // Recargar el iframe para refrescar el stream
        const currentSrc = videoIframe.src;
        videoIframe.src = '';
        setTimeout(() => {
            videoIframe.src = currentSrc;
        }, 100);
    }
}

function shareCamera(url, title) {
    if (navigator.share) {
        navigator.share({
            title: title,
            text: 'Mira esta cámara en vivo en ECURAICES WEBCAMS',
            url: url
        }).catch(err => {
            console.log('Error al compartir:', err);
            fallbackShare(url);
        });
    } else {
        fallbackShare(url);
    }
}

function fallbackShare(url) {
    // Crear un input temporal para copiar al portapapeles
    const input = document.createElement('input');
    input.value = url;
    document.body.appendChild(input);
    input.select();
    document.execCommand('copy');
    document.body.removeChild(input);
    
    // Mostrar notificación
    showNotification('Enlace copiado al portapapeles');
}

function showNotification(message) {
    // Crear elemento de notificación
    const notification = document.createElement('div');
    notification.className = 'notification';
    notification.textContent = message;
    notification.style.cssText = `
        position: fixed;
        bottom: 20px;
        right: 20px;
        background: #2574b4;
        color: white;
        padding: 1rem 2rem;
        border-radius: 10px;
        box-shadow: 0 4px 15px rgba(0,0,0,0.2);
        z-index: 9999;
        animation: slideIn 0.3s ease;
    `;
    
    document.body.appendChild(notification);
    
    setTimeout(() => {
        notification.style.animation = 'slideOut 0.3s ease';
        setTimeout(() => {
            document.body.removeChild(notification);
        }, 300);
    }, 3000);
}

// Agregar estilos de animación si no existen
if (!document.getElementById('notification-styles')) {
    const style = document.createElement('style');
    style.id = 'notification-styles';
    style.textContent = `
        @keyframes slideIn {
            from {
                transform: translateX(100%);
                opacity: 0;
            }
            to {
                transform: translateX(0);
                opacity: 1;
            }
        }
        @keyframes slideOut {
            from {
                transform: translateX(0);
                opacity: 1;
            }
            to {
                transform: translateX(100%);
                opacity: 0;
            }
        }
    `;
    document.head.appendChild(style);
}


