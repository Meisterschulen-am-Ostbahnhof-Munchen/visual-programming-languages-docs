# AULI_DEMUX_4


![AULI_DEMUX_4](./AULI_DEMUX_4.svg)

* * * * * * * * * *
## Einleitung
Der **AULI_DEMUX_4** ist ein generischer Demultiplexer, der einen eingehenden AULI‑Adapter-Datenstrom an einen von vier möglichen Ausgangsadaptern weiterleitet. Die Auswahl erfolgt über einen numerischen Index (K), der beim Setzen des REQ‑Ereignisses ausgewertet wird. Der Baustein ist für den Einsatz in der landwirtschaftlichen Automatisierungstechnik (AULI) konzipiert und erlaubt eine flexible Verteilung von Signalen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ | Event | Setzt den Index K und löst die Demultiplexing‑Operation aus. |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF | Event | Bestätigt die erfolgreiche Weiterleitung an den ausgewählten Adapter. |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K | UINT | Index (Wertebereich 0–3 für OUT1…OUT4) |

### **Daten-Ausgänge**
*Keine*

### **Adapter**

| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| IN | AULI | Socket (Eingang) | Eingangsadapter mit den zu verteilenden Daten |
| OUT1 | AULI | Plug (Ausgang) | Erster Ausgang (bei K=0) |
| OUT2 | AULI | Plug (Ausgang) | Zweiter Ausgang (bei K=1) |
| OUT3 | AULI | Plug (Ausgang) | Dritter Ausgang (bei K=2) |
| OUT4 | AULI | Plug (Ausgang) | Vierter Ausgang (bei K=3) |

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert:
1. Ein REQ‑Ereignis wird empfangen.
2. Der aktuelle Wert des Daten‑Eingangs **K** wird gelesen.
3. Der Zustand des Socket‑Adapters **IN** wird an den Plug‑Adapter **OUT1**, **OUT2**, **OUT3** oder **OUT4** kopiert, abhängig vom Wert von K (z.B. K=0 → OUT1, K=1 → OUT2, …).
4. Nach erfolgreicher Übertragung wird das **CNF**‑Ereignis ausgegeben.

Der Baustein ist generisch (GenericClassName `'GEN_AULI_DEMUX'`) und kann durch Parametrisierung an verschiedene AULI‑Untertypen angepasst werden.

## Technische Besonderheiten
- **Adapterbasiert**: Die Ein‑ und Ausgaben erfolgen ausschließlich über AULI‑Adapter, was eine lose Kopplung und modulare Wiederverwendung ermöglicht.
- **Unidirektional**: Der Datenfluss verläuft nur vom Socket **IN** zu einem der Plugs; eine Rückkopplung ist nicht vorgesehen.
- **Generisch**: Der Baustein ist als Vorlage (Generic FB) definiert, sodass er mit unterschiedlichen AULI‑Datentypen verwendet werden kann.
- **Einfache Indizierung**: Der Index K ist als UINT ausgeführt (Werte 0 bis 3). Bei ungültigen Werten ist das Verhalten undefiniert (keine Bereichsprüfung im FB‑Interface).

## Zustandsübersicht
Der Baustein besitzt keine explizite Zustandsmaschine (ECC) im XML. Seine Funktionalität reduziert sich auf eine reine Ereignis‑Daten‑Transaktion:
- **IDLE**: Warten auf REQ.
- **ACTIVE**: Kopieren des IN‑Adapterwerts auf den durch K bestimmten OUT‑Adapter.
- **DONE**: Ausgabe von CNF und Rückkehr nach IDLE.

Eine detaillierte Zustandsgraphik ist nicht erforderlich, da der Baustein atomar arbeitet.

## Anwendungsszenarien
- **Verteilung von Sensordaten**: Ein AULI‑Sensor (z.B. Bodenfeuchte) wird nacheinander an verschiedene Aktor‑Einheiten weitergeleitet.
- **Kanalumschaltung**: Steuerung von vier unterschiedlichen Verbrauchern (Ventilen, Motoren) über eine gemeinsame Datenquelle.
- **Test- und Simulationsumgebungen**: Gezieltes Ansprechen einzelner Komponenten in einer AULI‑basierten Testplattform.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Typ | Unterschied |
|----------|-----|-------------|
| AULI_MUX_4 | Multiplexer | Fasst mehrere AULI‑Eingänge zu einem Ausgang zusammen (umgekehrte Richtung). |
| AULI_DEMUX_2 | Demultiplexer (2‑fach) | Gleiche Funktionsweise, jedoch nur zwei Ausgänge. |
| AULI_SWITCH | Umschalter | Ermöglicht dynamisches Verbinden zwischen mehreren Ein‑ und Ausgängen (Matrix‑Topologie). |

## Fazit
Der **AULI_DEMUX_4** ist ein kompakter, generischer Demultiplexer für AULI‑Adapter, der sich ideal für die gezielte Verteilung von Datenströmen in der Agrartechnik eignet. Dank seiner einfachen Ereignissteuerung und Adapterschnittstelle lässt er sich leicht in bestehende 4diac‑Prozessketten integrieren. Die generische Natur erlaubt Anpassungen ohne Änderung der Bausteinlogik.