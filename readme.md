

<h2>
    Trabajo final para la carrera de especialista en sistemas embebidos: 
    Sistema de telemetría para usos en investigación.
</h2>

## Alumno: German Velardez

### Breve resumen del proyecto a realizar:



<p>Se pretende diseñar el firmware de un drifter modular. La arquitectura del mismo debe tener una estructura en capas.
</p>


 <h4 align="center">Diagrama simple del sistema</h4>
 <div align="center" >
<img  src="diagrama_sistema.jpg" border="1px" 
     height="320px" width="480px"/>
</div>

### El proyecto esta basado en un microcontrolador en rp2040. Como herramientas de desarrollo se utiliza las siguientes:
<lu>
    <li>
            pico-sdk: <A HREF="https://github.com/FreeRTOS/FreeRTOS-Kernel">repo</A>
    </li> 
    <li>
            Freertos: <A HREF="https://github.com/raspberrypi/pico-sdk">repo</A>
    </li> 
</lu>


Asegurese de tener instalado las herramientas necesaria para utilizar el pico-sdk y tambien haber agregado la variable de entorno **PICO_SDK_PATH**

Para iniciar el proyecto ejecute el siguiente comando:
```
    ./runCode.sh
```
En caso de recibir error de permiso denegado debera ejecutar primero:
```
     sudo chmod +x runCode.sh
```
Para luego reintentar con el primer comando. 

Luego de ejecutado con exito el primer comando se creara una carpeta llamada build, ingrese en ella y ejecute:
```
    make simo
 ```
 Luego de compilarse el codigo se generaran varios archivos. El simo.uf2 es el que debera introducir en el microcontrolador raspberry pi pico. No olvide antes de conectar el micro, tener el boton boot presionado. 
 
 
 Para generar la documentacion necesita tener instalado Doxygen en su computadora. Comando de generacion:
```
    doxygen doc_config
 ```


