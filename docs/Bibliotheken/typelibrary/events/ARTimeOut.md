# ARTimeOut

![ARTimeOut](https://user-images.githubusercontent.com/116869307/214142115-28b88284-c3b6-4c78-9145-6de372738f36.png)

* * * * * * * * * *  

## Einleitung  

Die IEC 61499 ist ein internationaler Standard für die Modellierung verteilter industrieller Steuerungssysteme. Innerhalb dieses Standards sind Adaptertypen eine wichtige Komponente, um wiederverwendbare Schnittstellen zwischen Funktionsbausteinen zu definieren. Der **ARTimeOut**-Adapter (Adapter for Resettable Timeout) ist ein Beispiel für einen solchen Adapter, der eine Schnittstelle für einen rücksetzbaren Timeout-Service bereitstellt. 

## Struktur des ARTimeOut-Adapters  

Der ARTimeOut-Adapter ist als **AdapterType** in der IEC 61499 spezifiziert und definiert eine Schnittstelle für die Kommunikation zwischen einem SOCKET und einem PLUG.  

### Schnittstelle (Interface)  

Die Schnittstelle des ARTimeOut-Adapters besteht aus:  

- **Eingangsereignisse (Event Inputs)**:  
  - **TimeOut**: Dieses Ereignis wird vom SOCKET ausgelöst, um anzuzeigen, dass der Timeout abgelaufen ist.  

- **Ausgangsereignisse (Event Outputs)**:  
  - **START**: Dieses Ereignis wird vom PLUG ausgelöst, um den Timeout zu starten oder zurückzusetzen. Es ist mit der Ausgangsvariablen **DT** verknüpft, die die Timeout-Dauer definiert.  
  - **STOP**: Dieses Ereignis wird vom PLUG ausgelöst, um den Timeout anzuhalten.  

- **Ausgangsvariable (Output Variable)**:  
  - **DT (Duration Time)**: Eine Zeitvariable (TIME), die die Dauer des Timeouts angibt.  

### Service-Verhalten  

Der ARTimeOut-Adapter bietet zwei Service-Sequenzen:  

1. **Timeout**:  
   - Der PLUG sendet ein **START**-Ereignis mit der Zeitdauer **DT**, um den Timeout zu starten.  
   - Wenn der Timeout abläuft, sendet der SOCKET ein **TimeOut**-Ereignis zurück an den PLUG.  

2. **NormalOperation**:  
   - Der PLUG sendet ein **START**-Ereignis mit der Zeitdauer **DT**, um den Timeout zu starten.  
   - Der PLUG kann ein **STOP**-Ereignis senden, um den Timeout vorzeitig zu beenden.  

## Verhalten des ARTimeOut-Adapters  

Der ARTimeOut-Adapter ermöglicht die Steuerung eines Timeout-Mechanismus mit folgenden Funktionen:  

1. **Start/Reset des Timeouts**:  
   - Durch das **START**-Ereignis wird der Timeout mit der angegebenen Dauer **DT** gestartet oder zurückgesetzt.  

2. **Stop des Timeouts**:  
   - Das **STOP**-Ereignis beendet den Timeout vorzeitig.  

3. **Timeout-Ablauf**:  
   - Wenn der Timeout abläuft, wird das **TimeOut**-Ereignis ausgelöst, um den PLUG zu benachrichtigen.  

## Anwendungsbeispiele  

Der ARTimeOut-Adapter kann in verschiedenen industriellen Steuerungsanwendungen eingesetzt werden, insbesondere in Szenarien, in denen ein zuverlässiger und rücksetzbarer Timeout-Mechanismus erforderlich ist. Beispiele sind:  

- **Netzwerkkommunikation**: Überwachung von Antwortzeitüberschreitungen in verteilten Systemen.  
- **Maschinensteuerung**: Timeout für die Ausführung von Befehlen, um hängende Prozesse zu erkennen.  
- **Sicherheitssysteme**: Überwachung von Sensoren, um Fehlfunktionen zu erkennen, wenn keine Aktualisierungen erfolgen.  

## Fazit  

Der ARTimeOut-Adapter ist ein nützliches Werkzeug in der IEC 61499, um eine standardisierte Schnittstelle für rücksetzbare Timeout-Services bereitzustellen. Durch seine klare Trennung zwischen SOCKET und PLUG sowie die definierten Service-Sequenzen eignet er sich ideal für die Integration in verteilte Steuerungssysteme. Die Fähigkeit, den Timeout zu starten, zu stoppen und bei Ablauf zu benachrichtigen, macht ihn zu einer flexiblen Lösung für eine Vielzahl von industriellen Anwendungen.  