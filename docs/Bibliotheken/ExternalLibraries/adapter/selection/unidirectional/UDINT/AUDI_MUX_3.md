# AUDI_MUX_3

(Kein Bild verfügbar)


![AUDI_MUX_3](./AUDI_MUX_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUDI_MUX_3` ist ein generischer Multiplexer (MUX), der es ermöglicht, aus drei Adapter-Eingängen (IN1, IN2, IN3) des Typs `adapter::types::unidirectional::AUDI` einen auszuwählen und auf den Adapter-Ausgang `OUT` zu legen. Die Auswahl erfolgt über den am Daten-Eingang `K` angelegten Index (0, 1 oder 2) und wird durch ein Ereignis am Eingang `REQ` ausgelöst. Der Baustein ist für die Verwendung in Systemen der Automatisierungstechnik konzipiert, die den AUDI‑Adapterstandard nutzen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `REQ`    | Mit diesem Ereignis wird die Umschaltung auf den durch den Index `K` festgelegten Adapter-Eingang ausgelöst. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Bestätigung, dass die gewünschte Adapterverbindung hergestellt wurde. |

### **Daten-Eingänge**

| Name | Typ   | Beschreibung                                      |
|------|-------|---------------------------------------------------|
| `K`  | UINT  | Index des auszuwählenden Adapter-Eingangs (0, 1 oder 2). |

### **Daten-Ausgänge**

Keine separaten Daten-Ausgänge. Die Ausgabe erfolgt über den Adapter-Ausgang `OUT`.

### **Adapter**

| Richtung | Name | Typ                                        | Beschreibung                                         |
|----------|------|--------------------------------------------|------------------------------------------------------|
| Plug     | `OUT`| `adapter::types::unidirectional::AUDI`    | Ausgangsadapter, der den gewählten Eingang bereitstellt. |
| Socket   | `IN1`| `adapter::types::unidirectional::AUDI`    | Erster Eingangsadapter (wird bei `K=0` durchgeschaltet). |
| Socket   | `IN2`| `adapter::types::unidirectional::AUDI`    | Zweiter Eingangsadapter (wird bei `K=1` durchgeschaltet). |
| Socket   | `IN3`| `adapter::types::unidirectional::AUDI`    | Dritter Eingangsadapter (wird bei `K=2` durchgeschaltet). |

## Funktionsweise

Der Baustein arbeitet ereignisgesteuert. Sobald das Ereignis `REQ` eintrifft, wird der aktuelle Wert des Daten-Eingangs `K` ausgewertet. Dieser Wert kann 0, 1 oder 2 sein. Der Funktionsblock leitet dann die Daten‑ und Ereignisschnittstelle des entsprechenden Socket-Adapters (`IN1`, `IN2` oder `IN3`) auf den Plug-Adapter `OUT`. Anschließend wird das Bestätigungsereignis `CNF` gesendet. Die Umschaltung erfolgt sofort, ohne dass eine interne Zustandsmaschine durchlaufen wird. Der Baustein ist als generischer Funktionsblock (`GenericClassName = 'GEN_AUDI_MUX'`) implementiert, d. h. er kann für beliebige Adaptertypen instanziiert werden, solange diese den `AUDI`-Typ verwenden.

## Technische Besonderheiten

- **Generischer Typ**: Der Baustein ist als `generic FB` deklariert, was bedeutet, dass der konkrete Adaptertyp zur Laufzeit festgelegt werden kann. In der vorliegenden Konfiguration wird der Adaptertyp `adapter::types::unidirectional::AUDI` verwendet.
- **Indexbereich**: Der Index `K` ist als `UINT` definiert; es werden jedoch nur die Werte 0, 1 und 2 sinnvoll verarbeitet. Werte außerhalb dieses Bereichs führen zu undefiniertem Verhalten.
- **EPL 2.0 Lizenz**: Der Baustein wird unter der Eclipse Public License 2.0 bereitgestellt (Copyright HR Agrartechnik GmbH).
- **Keine internen Zustände**: Der Funktionsblock besitzt keine dokumentierte Zustandsmaschine, sondern arbeitet rein transaktionsbasiert.

## Zustandsübersicht

Der `AUDI_MUX_3` verfügt über keine explizite Zustandsmaschine. Die Funktionsweise lässt sich als Ein-Schritt-Aktion beschreiben:

1. Warten auf Ereignis `REQ`.
2. Auswerten von `K`.
3. Durchschalten des entsprechenden Eingangsadapters auf `OUT`.
4. Senden von `CNF`.
5. Rückkehr in den Wartezustand.

## Anwendungsszenarien

- **Signalkonfiguration**: In einer Steuerung können mehrere gleichartige AUDI‑Signale (z. B. Messwerte) vorliegen, die je nach Betriebsmodus ausgewählt werden sollen.
- **Umschaltung zwischen Sensoren**: Drei Sensoren liefern Daten über einen AUDI‑Adapter; der Multiplexer wählt den aktiven Sensor aus.
- **Test-/Bypass-Modus**: Ein Modul kann wahlweise im Normalbetrieb (IN1), im Testmodus (IN2) oder im Bypass (IN3) betrieben werden.

## Vergleich mit ähnlichen Bausteinen

- **AUDI_MUX_2**: Ein Multiplexer für zwei Eingänge – analog aufgebaut, jedoch mit nur zwei Socket-Adaptern.
- **Standard‑MUX**: Herkömmliche Multiplexer (z. B. `MUX2` oder `MUX4`) arbeiten meist auf Datentygebene (z. B. `ANY`), während `AUDI_MUX_3` speziell für Adapter‑Schnittstellen konzipiert ist und die gesamte Adapter‑Verbindung inklusive Ereignissen weiterleitet.
- **Conditional‑Adapter**: Einige Bibliotheken bieten bedingte Adapter‑Weiterleitungen an, jedoch meist mit aufwändigerer Zustandslogik.

## Fazit

Der `AUDI_MUX_3` ist ein kompakter, generischer Funktionsblock zur einfachen Auswahl eines von drei gleichartigen AUDI‑Adapter‑Eingängen. Durch seine ereignisgesteuerte Arbeitsweise und die reduzierte Schnittstelle eignet er sich hervorragend für schnelle Umschaltaufgaben in Automatisierungsanwendungen. Die Rückmeldung über das `CNF`-Ereignis erlaubt eine zuverlässige Synchronisation im Steuerungsablauf.