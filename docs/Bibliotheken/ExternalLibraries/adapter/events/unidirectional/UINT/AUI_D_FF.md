# AUI_D_FF


![AUI_D_FF](./AUI_D_FF.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein **AUI_D_FF** realisiert ein taktgesteuertes D‑Flipflop (Data Latch). Er übernimmt den Wert eines Dateneingangs bei einem anliegenden Ereignis und gibt den gespeicherten Wert am Ausgang aus. Die Ein‑ und Ausgangsschnittstellen sind als unidirektionale **Adapter** ausgeführt, was eine flexible und standardisierte Verbindung in der 4diac‑IDE ermöglicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine – die Ereignissteuerung erfolgt ausschließlich über den Adapter **I**.

### **Ereignis-Ausgänge**
Keine – die Ereignisausgabe erfolgt ausschließlich über den Adapter **Q**.

### **Daten-Eingänge**
Keine – die Datenübergabe erfolgt ausschließlich über den Adapter **I**.

### **Daten-Ausgänge**
Keine – die Datenausgabe erfolgt ausschließlich über den Adapter **Q**.

### **Adapter**

| Bezeichnung | Typ | Richtung | Beschreibung |
|-------------|-----|----------|--------------|
| **I** | `adapter::types::unidirectional::AUI` | Socket (Eingang) | Eingangswert (D) und Taktereignis (CLK) |
| **Q** | `adapter::types::unidirectional::AUI` | Plug (Ausgang) | Gespeicherter Wert (Q) und Ausgabeereignis (EO) |

Der Adaptertyp **AUI** bietet einen unidirektionalen Kanal, der genau ein Ereignis und einen Datenwert überträgt. Somit werden die internen Verbindungen zwischen dem Flipflop und der Außenwelt über Adapter realisiert.

## Funktionsweise
Der FB nutzt intern den Baustein `E_D_FF_ANY` aus der IEC‑61499‑Standardbibliothek.  
- Bei jedem **Taktereignis** auf `I.E1` wird der aktuelle Datenwert von `I.D1` übernommen.  
- Der übernommene Wert wird am Ausgang `Q.D1` bereitgestellt und parallel ein **Ausgabeereignis** auf `Q.E1` ausgelöst.  
- Der gespeicherte Wert bleibt solange erhalten, bis ein neues Taktereignis einen neuen Datenwert übernimmt.

## Technische Besonderheiten
- Die Schnittstelle besteht ausschließlich aus **Adaptern**, nicht aus getrennten Ereignis‑ und Datenports. Dies erlaubt eine lose Kopplung und Wiederverwendbarkeit des Adaptertyps in verschiedenen Kontexten.
- Der Adapter `AUI` ist **unidirektional** – Daten und Ereignisse fließen nur in eine Richtung.
- Der Baustein ist typsicher: Der Datentyp wird durch den Adapter vorgegeben (im Standard `ANY`).

## Zustandsübersicht
Der FB besitzt zwei logische Zustände, die dem internen Flipflop entsprechen:

| Zustand | Beschreibung |
|---------|--------------|
| **Q = 0** | Ausgangswert ist LOW (logisch 0). |
| **Q = 1** | Ausgangswert ist HIGH (logisch 1). |

Der Zustand wechselt ausschließlich bei einer steigenden Flanke des Taktereignisses (sofern das Ereignis im Adapter ausgelöst wird).

## Anwendungsszenarien
- **Synchronisation**: Übernahme eines Datenwertes genau zu einem definierten Zeitpunkt (z.B. bei einem Sensor‑Event).
- **Zwischenspeicher**: Puffern eines Wertes für die Weiterverarbeitung in nachfolgenden Bausteinen.
- **Zustandsmaschinen**: Speicherung von Zuständen in diskreten Steuerungen, wenn eine einfache D‑Flipflop‑Funktion ausreicht.

## Vergleich mit ähnlichen Bausteinen
- **E_D_FF** (Standard‑IEC‑61499): Bietet dieselbe Flipflop‑Funktionalität, jedoch mit separaten Ereignis‑ und Datenports. Der `AUI_D_FF` kapselt diese Ports in einem Adapter und ermöglicht so eine saubere, adapterbasierte Kommunikation.
- **E_RS** oder **E_SR** (Reset‑Set‑Flipflops): Im Gegensatz zum D‑Flipflop benötigen diese Bausteine separate Set‑/Reset‑Ereignisse und keinen Takt. Der `AUI_D_FF` ist für taktgesteuerte Anwendungen optimiert.

## Fazit
Der `AUI_D_FF` stellt ein standardkonformes D‑Flipflop in der 4diac‑IDE dar, das durch die Verwendung von **Adaptern** eine modulare und wiederverwendbare Schnittstelle bietet. Er eignet sich besonders für Anwendungen, bei denen eine einheitliche, unidirektionale Verbindungsstruktur gewünscht ist, ohne auf die bewährte Flipflop‑Logik verzichten zu müssen.