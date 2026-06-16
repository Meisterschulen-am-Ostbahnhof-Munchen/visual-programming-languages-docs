# AE_DEMUX_3


![AE_DEMUX_3](./AE_DEMUX_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AE_DEMUX_3** ist ein generischer AE-Demultiplexer.  
Er leitet einen über den Adapter-Eingang `IN` anliegenden AE-Wert wahlweise auf einen von drei Adapter-Ausgängen (`OUT1` bis `OUT3`) weiter. Die Auswahl des Ausgangs erfolgt über den Index `K`, der bei einem Ereignis am Eingang `REQ` ausgewertet wird.

Der Baustein ist als generischer FB (GenericClassName `GEN_AE_DEMUX`) realisiert und wird erst zur Übersetzungszeit oder bei der Instanziierung auf die konkrete Anzahl von Ausgängen spezialisiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `REQ`    | Übernahme des Index `K` und Weiterleitung des Adapter-Eingangs auf einen der drei Ausgänge |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Bestätigung der abgeschlossenen Weiterleitung |

### **Daten-Eingänge**

| Name | Typ   | Beschreibung |
|------|-------|--------------|
| `K`  | UINT  | Index des ausgewählten Ausgangs (gültige Werte: 1, 2 oder 3) |

### **Daten-Ausgänge**
*Keine direkten Datenausgänge vorhanden. Die Ausgangsdaten werden über die Adapter-Ausgänge bereitgestellt.*

### **Adapter**

| Adapter | Richtung | Typ                                  | Beschreibung |
|---------|----------|--------------------------------------|--------------|
| `IN`    | Socket   | `adapter::types::unidirectional::AE` | Eingangs-AE-Signal |
| `OUT1`  | Plug     | `adapter::types::unidirectional::AE` | Erster Ausgang |
| `OUT2`  | Plug     | `adapter::types::unidirectional::AE` | Zweiter Ausgang |
| `OUT3`  | Plug     | `adapter::types::unidirectional::AE` | Dritter Ausgang |

## Funktionsweise

1. Der Baustein wartet auf ein Ereignis am Eingang `REQ`.
2. Mit dem Ereignis wird der ganzzahlige Wert des Daten-Eingangs `K` ausgelesen.
3. Abhängig vom Wert `K` wird der am Adapter-Socket `IN` anliegende AE-Wert auf einen der drei Adapter-Plugs weitergeleitet:
   - `K = 1` → Weiterleitung an `OUT1`
   - `K = 2` → Weiterleitung an `OUT2`
   - `K = 3` → Weiterleitung an `OUT3`
4. Nach erfolgreicher Weiterleitung wird das Ereignis `CNF` ausgegeben.

Sollte `K` außerhalb des gültigen Bereichs liegen, bleibt die Weiterleitung aus (`CNF` wird dennoch gesendet – je nach Implementierung).

## Technische Besonderheiten

- **Generischer Baustein:** Der FB ist als generisch deklariert (`GenericClassName = 'GEN_AE_DEMUX'`) und kann in der 4diac-IDE auf andere Ausgangsanzahlen erweitert werden.
- **Adapterbasierte Schnittstelle:** Ein- und Ausgänge sind als Adapter vom Typ `adapter::types::unidirectional::AE` definiert, was eine flexible Kopplung mit anderen AE-kompatiblen Bausteinen ermöglicht.
- **Lizenz und Herkunft:** Der Baustein wird unter der Eclipse Public License 2.0 bereitgestellt (Copyright 2026 HR Agrartechnik GmbH). Die Versionsinformationen zeigen den Autor Franz Höpfinger und das Datum 2026-05-28.

## Zustandsübersicht

Eine explizite Zustandsmaschine (ECC) ist in der vorliegenden XML nicht definiert. Daher wird das Verhalten als rein funktional ohne interne Zustände angenommen:  
- Bei jedem `REQ`-Ereignis erfolgt unverzüglich die Indexauswertung und Weiterleitung.
- Nach der Aktion wird sofort `CNF` gesendet.

## Anwendungsszenarien

- **Signalverteilung in Automatisierungssystemen:** Ein eingehendes AE-Signal kann wahlweise an eine von drei nachgelagerten Stationen oder Subsysteme weitergeleitet werden.
- **Kanalauswahl:** In einer Kommunikationskette wird der Datenpfad über `K` dynamisch umgeschaltet.
- **Test- und Debugging-Umgebungen:** Ein Testsignal kann auf verschiedene Analysegeräte geroutet werden.

## Vergleich mit ähnlichen Bausteinen

- **AE_DEMUX_2:** Ein Demultiplexer mit zwei Ausgängen – gleiche Funktionsweise, aber geringere Anzahl an Auswahlmöglichkeiten.
- **AE_MUX_3 (Multiplexer):** Der umgekehrte Baustein, der mehrere AE-Eingänge auf einen Ausgang zusammenführt.
- **Nicht-generische Demultiplexer:** Diese Bausteine haben fest verdrahtete Ausgangsanzahlen und können nicht auf andere Konfigurationen angepasst werden. Der AE_DEMUX_3 bietet durch seinen generischen Ansatz mehr Flexibilität.

## Fazit

Der **AE_DEMUX_3** ist ein kompakter, generischer Demultiplexer für AE-Signale, der mit minimalem Aufwand eine gezielte Signalweiterleitung auf drei Ausgänge erlaubt. Durch die Verwendung von Adaptern und die generische Architektur eignet er sich gut für modulare und wiederverwendbare Automatisierungslösungen. Die klare Ereignisschnittstelle (REQ/CNF) erleichtert die Integration in ereignisgesteuerte Steuerungsabläufe.