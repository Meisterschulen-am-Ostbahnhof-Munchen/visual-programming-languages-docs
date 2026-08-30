# Q_BackgroundColourAux_AUS

![Q_BackgroundColourAux_AUS](./Q_BackgroundColourAux_AUS.svg)

* * * * * * * * * *

## Einleitung

Dieser Funktionsblock implementiert das Kommando zum Ändern der Hintergrundfarbe eines Objekts gemäß ISO 11783-6, Teil F.20.  
Er ermöglicht die Interaktion mit dem Virtuellen Terminal (VT) und übernimmt die Übermittlung der neuen Farbe sowie die Rückmeldung des Ergebnisses.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Mit Parameter | Beschreibung |
|----------|-------|----------------|--------------|
| INIT     | EInit | u16ObjId       | Service Initialisierung |

### **Ereignis-Ausgänge**

| Ereignis | Typ    | Mit Parameter | Beschreibung |
|----------|--------|----------------|--------------|
| INITO    | EInit  | –              | Initialisierung bestätigt |
| CNF      | Event  | STATUS, s16result | Bestätigung des angeforderten Dienstes |

### **Daten-Eingänge**

| Name      | Typ   | Initialwert | Beschreibung |
|-----------|-------|-------------|--------------|
| u16ObjId  | UINT  | ID_NULL     | Objekt-ID des betroffenen Objekts |

### **Daten-Ausgänge**

| Name      | Typ    | Beschreibung |
|-----------|--------|--------------|
| STATUS    | STRING | Dienststatus (z. B. Fehlertext) |
| s16result | INT    | Rückgabewert (siehe unten) |

### **Adapter**

| Richtung | Name        | Typ  | Beschreibung |
|----------|-------------|------|--------------|
| Socket   | u8Colour    | AUS  | Neue Hintergrundfarbe (gemäß ISO 11783-6 A.3) |
| Plug     | u8OldColour | AUS  | Alte Hintergrundfarbe (wird vom VT zurückgemeldet) |

## Gültige Objekt-IDs

`u16ObjId` ist für dieselben Objekttypen gültig wie beim umschlossenen Basisbaustein `Q_BackgroundColourAux` / `Q_BackgroundColour` (Anhang F.20, Objekte mit Hintergrundfarben-Attribut): WorkingSet (0), Data Mask (1000–1999), Alarm Mask (2000–2999), Soft Key Mask (4000–4999), Key (5000–5999), Button (6000–6999), Input Boolean Field (7000–7999), Input String Field (8000–8999), Input Number Field (9000–9999), Output String Field (11000–11999), Output Number Field (12000–12999), Window Mask (34000–34999), Graphics Context (36000–36999), Auxiliary Function (29000–29999), Auxiliary Function Type2 (31000–31999), Auxiliary Input Type2 (32000–32999).

ID_NULL (65535) ist kein gültiges Kommandoziel, deaktiviert aber bei `INIT` den Baustein.

## Funktionsweise

Der Baustein erwartet zuerst eine Initialisierung mit der Objekt-ID (`INIT` mit `u16ObjId`).  
Sobald am Socket-Adapter `u8Colour` ein neuer Farbwert anliegt (ausgelöst durch das Ereignis `E1` des Adapters), wird intern ein `REQ`-Event an den verkapselten Funktionsblock `Q_BackgroundColourAux` gesendet.  
Dieser führt das VT-Kommando aus und liefert über den Ausgang `CNF` den Status (`STATUS`) und das Ergebnis (`s16result`) zurück.  
Die alte Farbe wird über den Plug-Adapter `u8OldColour` ausgegeben.  

Die gesamte Logik ist in einem untergeordneten FB der gleichen Familie gekapselt, sodass dieser Baustein nur als äußere Hülle für die Adapterkopplung dient.

## Technische Besonderheiten

- Der Initialwert für `u16ObjId` ist `ID_NULL`, d. h. der FB muss vor der Nutzung mit einer gültigen Objekt-ID initialisiert werden.
- Die Farbwerte werden als 8‑Bit-Werte über den AUS‑Adapter transportiert. Die gültigen Farben sind in der VT‑Standard‑Farbpalette (ISO 11783‑6 Anhang A.3) definiert.
- Mögliche Rückgabewerte (`s16result`):
  - `VT_E_NO_ERR` (0): Erfolg
  - `VT_E_OVERFLOW` (-6): Pufferüberlauf
  - `VT_E_NOACT` (-8): Kommando im aktuellen Zustand nicht möglich
  - `VT_E_NO_INSTANCE` (-21): Kein VT‑Client verfügbar
  - `VT_E_ISO_INSTANCE_INVALID` (-129): Ungültige Verbindungskennung
  - `VT_E_NOT_ALIVE` (-130): VT‑Instanz gültig, aber VT nicht erreichbar

## Zustandsübersicht

Der FB besitzt keine expliziten Zustandsautomaten im XML. Die Ereignissteuerung erfolgt rein über die Ereignisverbindungen:

1. **INIT** → Initialisierung des Dienstes.
2. **Externes Ereignis über Socket‑Adapter** → Start des Farbänderungs‑Requests.
3. **CNF** → Abschluss der Operation mit Status und Rückgabewert.

## Anwendungsszenarien

- Dynamische Anpassung der Hintergrundfarbe eines ISOBUS‑VT‑Objekts (z. B. Button, Textfeld) in Abhängigkeit von Betriebszuständen oder Benutzereingaben.
- Umsetzung von Farbwechseln in landwirtschaftlichen Steuerungs‑ und Visualisierungssystemen.

## Vergleich mit ähnlichen Bausteinen

Es existieren analoge Funktionsblöcke für andere visuelle Eigenschaften (z. B. `Q_TextColourAux_AUS`, `Q_VisibilityAux_AUS`).  
Gemeinsam ist allen das schema-basierte Adapter-Pattern, das die Signalisierung von Wertänderungen über AUS‑Adapter realisiert.  
Dieser Baustein spezialisiert sich auf die Hintergrundfarbe und verwendet die gleichen Fehler- und Rückgabewerte.

## Fazit

Der Funktionsblock `Q_BackgroundColourAux_AUS` kapselt einen ISOBUS‑VT‑Dienst zur Hintergrundfarbänderung kompakt und bietet durch die Adapterschnittstellen eine einfache Integration in übergeordnete Steuerungen.  
Er ist zuverlässig, standardkonform und erlaubt durch die Rückmeldung des Status eine robuste Fehlerbehandlung.
