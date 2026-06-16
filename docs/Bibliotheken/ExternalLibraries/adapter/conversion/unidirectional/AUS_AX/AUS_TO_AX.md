# AUS_TO_AX


![AUS_TO_AX](./AUS_TO_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AUS_TO_AX** ist ein Composite-FB zur Konvertierung eines **AUS**-Adapters (Daten vom Typ USINT) in einen **AX**-Adapter (Daten vom Typ BOOL).  
Er vergleicht den eingehenden USINT-Wert mit Null und gibt das Ergebnis als Boolesches Signal aus. Dies ermöglicht eine einfache Umsetzung von Zähler- oder Sensordaten in ein binäres Statusignal.

## Schnittstellenstruktur
Der FB bietet keine direkten Ereignis- oder Datenanschlüsse, sondern ausschließlich Adapter-Schnittstellen.

### **Ereignis-Eingänge**
Keine direkten Ereigniseingänge. Das Ereignissignal wird über den Adapter **AUS\_IN.E1** bereitgestellt.

### **Ereignis-Ausgänge**
Keine direkten Ereignisausgänge. Das Ereignissignal wird über den Adapter **AX\_OUT.E1** ausgegeben.

### **Daten-Eingänge**
Keine direkten Dateneingänge. Das Datensignal (USINT) wird über den Adapter **AUS\_IN.D1** bereitgestellt.

### **Daten-Ausgänge**
Keine direkten Datenausgänge. Das Datensignal (BOOL) wird über den Adapter **AX\_OUT.D1** ausgegeben.

### **Adapter**

| Name | Richtung | Typ | Kommentar |
|------|----------|-----|-----------|
| AUS\_IN | Socket | adapter::types::unidirectional::AUS | USINT-Eingangswert und Ereignis |
| AX\_OUT | Plug  | adapter::types::unidirectional::AX | BOOL-Ausgangswert und Ereignis |

## Funktionsweise
Der FB nutzt intern einen **F_NE**-Baustein (Vergleich auf Ungleichheit) aus der IEC‑61131‑Bibliothek.  
- Ein ankommendes Ereignis **AUS\_IN.E1** triggert den **REQ**-Eingang von **F_NE**.  
- **F_NE** vergleicht den Datenwert **AUS\_IN.D1** (USINT) mit dem konstanten Wert **USINT#0**.  
- Das Vergleichsergebnis (BOOL: TRUE, wenn ungleich Null, sonst FALSE) wird an **AX\_OUT.D1** weitergeleitet.  
- Nach Abschluss der Verarbeitung erzeugt **F_NE** ein **CNF**-Ereignis, das auf **AX\_OUT.E1** übertragen wird.

## Technische Besonderheiten
- Der FB ist als **Composite-FB** realisiert, d.h. seine Logik wird durch ein internes Netzwerk aus Standardbausteinen abgebildet.
- Er verwendet den **F_NE**-Vergleichsbaustein, der der Bibliothek **iec61131::comparison** entstammt.
- Die Paketorganisation lautet **adapter::conversion::unidirectional**, was die Verwendung als Adapter-Konverter kennzeichnet.
- Der FB besitzt keine eigenen Zustandsautomaten; die Verarbeitung erfolgt ausschließlich ereignisgesteuert über die internen Verbindungen.

## Zustandsübersicht
Als Composite-FB besitzt **AUS_TO_AX** keinen eigenen Zustandsautomaten.  
Die gesamte Logik wird vom integrierten **F_NE** durchgeführt, das keine zustandsbehaftete Steuerung benötigt.  
Das Verhalten ist rein kombinatorisch mit ereignisgesteuerter Ausführung.

## Anwendungsszenarien
- Umwandlung eines Zählerwerts (USINT) in ein Bool-Signal, das den Zustand „Wert ≠ 0“ anzeigt (z.B. „Füllstand vorhanden“ oder „Sensor aktiv“).
- Einsatz in der **Agrartechnik** – der FB stammt aus dem Umfeld der HR Agrartechnik GmbH – zur Verarbeitung von Sensordaten über Adapter-Schnittstellen.
- Vereinfachung der Verkabelung in 4diac‑IDE‑Projekten, wenn heterogene Adapter‑Typen aufeinander abgestimmt werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Direkter Vergleich mit einem **NE**-Baustein: **AUS_TO_AX** erweitert die reine Vergleichsfunktion um eine Adapter-Konvertierung.  
- Während ein **NE**-FB üblicherweise zwei einfache Dateneingänge (z.B. ANY) erwartet, arbeitet dieser Baustein ausschließlich mit vordefinierten Adaptern (AUS / AX) und versteckt die interne Logik.  
- Er ist damit spezifisch für Systeme mit einheitlichem Adapter‑Konzept (unidirektionale Schnittstellen) optimiert.

## Fazit
**AUS_TO_AX** ist ein einfacher, aber zweckmäßiger Adapter-Konverter, der einen USINT-Wert über den Vergleich mit Null in ein Boolesches Signal umsetzt.  
Durch die Kapselung als Composite-FB mit Adapteranschlüssen lässt er sich sauber in modulare 4diac‑Projekte einbinden. Der FB bietet keine eigenen Zustände und ist aufgrund seiner geringen Komplexität zuverlässig und wartungsarm.