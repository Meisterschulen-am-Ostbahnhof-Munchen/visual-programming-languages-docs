# AS_TO_AD


![AS_TO_AD](./AS_TO_AD.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AS_TO_AD** ist ein zusammengesetzter Baustein (Composite FB), der eine SINT-Adapter-Schnittstelle (AS) in eine DWORD-Adapter-Schnittstelle (AD) umwandelt. Er dient als Konverter zwischen zwei unidirektionalen Adaptertypen und wird typischerweise eingesetzt, um Daten von einem SINT-basierten Signalweg an einen DWORD-basierten Signalweg anzupassen.

## Schnittstellenstruktur
Der Baustein besitzt keine eigenen Ereignis- oder Datenein-/ausgänge, sondern stellt ausschließlich Adapter-Schnittstellen zur Verfügung.

### **Ereignis-Eingänge**
- Keine direkten Ereigniseingänge – die Ereignissteuerung erfolgt über den eingehenden Adapter **AS_IN** (Socket).  
  Der Adapter liefert über seinen Ereignisausgang **E1** das Startsignal für die Umwandlung.

### **Ereignis-Ausgänge**
- Keine direkten Ereignisausgänge – die Ereignisausgabe erfolgt über den ausgehenden Adapter **AD_OUT** (Plug).  
  Nach abgeschlossener Umwandlung wird das Ereignis **E1** am ausgehenden Adapter gesendet.

### **Daten-Eingänge**
- Keine direkten Dateneingänge – der zu konvertierende SINT-Wert wird über den Adapter **AS_IN** (Socket) über dessen Datenausgang **D1** bereitgestellt.

### **Daten-Ausgänge**
- Keine direkten Datenausgänge – der konvertierte DWORD-Wert wird über den Adapter **AD_OUT** (Plug) über dessen Dateneingang **D1** ausgegeben.

### **Adapter**
| Adaptername | Richtung | Typ | Beschreibung |
|-------------|----------|-----|--------------|
| **AS_IN** | Socket (Eingang) | adapter::types::unidirectional::AS | Eingangsadapter für den SINT-Wert (inkl. Ereignis E1) |
| **AD_OUT** | Plug (Ausgang) | adapter::types::unidirectional::AD | Ausgangsadapter für den konvertierten DWORD-Wert (inkl. Ereignis E1) |

## Funktionsweise
Der Baustein arbeitet als reine Durchleitung mit Datentypkonvertierung:

1. Über den Socket **AS_IN** wird ein Ereignis am Ausgang **E1** empfangen. Gleichzeitig liegt am Datenausgang **D1** des Sockets ein Wert vom Typ `SINT` an.
2. Das Ereignis wird an den internen Funktionsbaustein **Convert** (Typ `F_SINT_TO_DWORD`) weitergeleitet und triggert dessen Umwandlung.
3. Der `F_SINT_TO_DWORD`-Baustein wandelt den empfangenen `SINT`-Wert in einen `DWORD`-Wert um und gibt das Ergebnis an seinem Ausgang **OUT** aus.
4. Nach erfolgreicher Umwandlung wird das Ereignis **CNF** des internen Bausteins an den Plug **AD_OUT** übergeben, welcher daraufhin sein Ereignis **E1** auslöst. Gleichzeitig wird der konvertierte `DWORD`-Wert an den Dateneingang **D1** des Plugs weitergeleitet.

Die gesamte Verarbeitung erfolgt synchron und ohne Datenpufferung – jede Umwandlung wird unmittelbar durch ein eingehendes Ereignis gestartet und das Ergebnis sofort ausgegeben.

## Technische Besonderheiten
- **Unidirektionale Adapter**: Der Baustein nutzt ausschließlich unidirektionale Adapter (Socket für Eingang, Plug für Ausgang). Eine Rückwärtskommunikation ist nicht vorgesehen.
- **Wiederverwendbarer Standard-Baustein**: Die Konvertierung wird durch den IEC-61131-konformen Baustein `F_SINT_TO_DWORD` realisiert, der in der Bibliothek `iec61131::conversion` bereitsteht.
- **Composite-Architektur**: Der Baustein ist als Composite FB implementiert und erlaubt eine einfache Anpassung oder Wiederverwendung des internen Netzwerks.
- **Lizenz**: Der Baustein steht unter der Eclipse Public License 2.0 (EPL-2.0) und enthält einen entsprechenden Copyright-Hinweis.

## Zustandsübersicht
Der Baustein besitzt keinen eigenen Zustandsautomaten. Seine Funktionsweise ist rein ereignisgesteuert und datenflussbasiert:

1. **Warten auf Ereignis** – Der interne FB `Convert` wartet auf ein `REQ`-Ereignis (bereitgestellt durch **AS_IN.E1**).
2. **Konvertierung** – Ein eingehendes Ereignis startet die Umwandlung des SINT-Werts in einen DWORD-Wert.
3. **Ausgabe** – Nach Abschluss wird das Ereignis **CNF** vom internen FB erzeugt und der konvertierte Wert an den Ausgangsadapter weitergegeben.

> **Hinweis:** Da keine Verzögerung oder Pufferung stattfindet, kann während der Konvertierung kein weiteres Ereignis bearbeitet werden.

## Anwendungsszenarien
- **Anbindung von Sensoren**: Ein Sensor liefert Daten als SINT (z. B. 8‑Bit-Werte), während die Steuerungseinheit ausschließlich DWORD-Werte verarbeitet.
- **Systemintegration**: Bestehende Kommunikationsschnittstellen auf SINT-Basis sollen an ein System angebunden werden, das DWORD-Adapter erwartet.
- **Protokollumsetzung**: In modularen Fertigungsanlagen werden verschiedene Adaptertypen verwendet, die durch solche Konverter miteinander verbunden werden können.

## Vergleich mit ähnlichen Bausteinen
- **BYTE_TO_WORD, BYTE_TO_DWORD, WORD_TO_DWORD** – Entsprechende Konverter für andere Datentypen sind in der IEC-61131-Bibliothek vorhanden.
- **AS_TO_AD** unterscheidet sich durch die Verwendung von Adapter-Schnittstellen statt direkter Ein‑/Ausgänge. Dadurch eignet er sich besonders für den modularen Aufbau von Adapterketten.
- **Direkte Konverter-FBs** wie `F_SINT_TO_DWORD` bieten eine einfachere Schnittstelle (Ein‑/Ausgänge), während der Composite FB den Vorteil der Adapterkompatibilität hat.

## Fazit
Der **AS_TO_AD**-Funktionsblock ist ein spezialisierter Adapter-Konverter, der eine nahtlose Integration eines SINT-basierten Datenpfades in eine DWORD-basierte Architektur ermöglicht. Durch die Nutzung des standardisierten Bausteins `F_SINT_TO_DWORD` und die Implementierung als Composite FB ist er zuverlässig, erweiterbar und einfach in bestehende 4diac-Projekte einzubinden. Seine unidirektionale Auslegung macht ihn ideal für Anwendungen, bei denen Daten nur in eine Richtung fließen müssen.