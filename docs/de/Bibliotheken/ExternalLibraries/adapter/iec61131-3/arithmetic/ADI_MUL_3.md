# ADI_MUL_3


![ADI_MUL_3](./ADI_MUL_3.svg)

*Kein Bild verfügbar*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `ADI_MUL_3` ist ein generischer Arithmetik-Baustein für die 4diac-IDE. Er dient zur Multiplikation von drei numerischen Eingangswerten, die über standardisierte, unidirektionale Adapter übertragen werden. Durch die Kapselung der mathematischen Operation in einer Adapter-Schnittstelle eignet sich dieser Baustein besonders für modulare und saubere Anwendungsarchitekturen innerhalb des IEC 61499-Standards.

## Schnittstellenstruktur

Da es sich um einen adapterbasierten Funktionsbaustein handelt, besitzt der `ADI_MUL_3` keine direkten klassischen Ereignis- oder Daten-Pins auf oberster Ebene. Die gesamte Kommunikation wird über die Adapter-Schnittstellen abgewickelt.

### **Ereignis-Eingänge**

*Keine direkten Ereignis-Eingänge vorhanden (Steuerung erfolgt über die Adapter).*

### **Ereignis-Ausgänge**

*Keine direkten Ereignis-Ausgänge vorhanden (Steuerung erfolgt über die Adapter).*

### **Daten-Eingänge**

*Keine direkten Daten-Eingänge vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Daten-Ausgänge vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Adapter)**

*   **IN1** (Typ: `adapter::types::unidirectional::ADI`)
    *   Erster Multiplikand für die Berechnungsoperation.
*   **IN2** (Typ: `adapter::types::unidirectional::ADI`)
    *   Zweiter Multiplikand für die Berechnungsoperation.
*   **IN3** (Typ: `adapter::types::unidirectional::ADI`)
    *   Dritter Multiplikand für die Berechnungsoperation.

#### **Plugs (Ausgangs-Adapter)**

*   **OUT** (Typ: `adapter::types::unidirectional::ADI`)
    *   Ausgangsadapter, der das mathematische Produkt der drei Eingangswerte liefert.

## Funktionsweise

Sobald an den Eingangs-Adaptern (`IN1`, `IN2`, `IN3`) neue Werte signalisiert werden, führt der Baustein die Multiplikation durch. Das Ergebnis wird nach folgender Formel berechnet:

$$\text{OUT} = \text{IN1} \times \text{IN2} \times \text{IN3}$$

Das berechnete Ergebnis wird unmittelbar an den Ausgangs-Adapter `OUT` übergeben und ein entsprechendes Update-Ereignis über den Adapter weitergeleitet.

## Technische Besonderheiten

*   **Generischer Typ:** Der Baustein basiert auf der generischen Klasse `'GEN_ADI_MUL'`. Dies ermöglicht eine flexible Handhabung unterschiedlicher numerischer Datentypen (z. B. `INT`, `UINT`, `REAL`, `LREAL`), je nachdem, wie die zugrunde liegenden ADI-Adapter implementiert sind.
*   **Unidirektionale Adapter:** Die Verwendung des Typs `unidirectional::ADI` sorgt für einen klaren Datenfluss in eine Richtung, was die Kopplung zwischen Programmteilen minimiert und die Systemstabilität erhöht.

## Zustandsübersicht

Der Funktionsbaustein ist als rein mathematischer, zustandsloser Baustein (stateless) konzipiert. Er speichert keine internen Historienwerte. Jede Aktualisierung an den Eingängen führt zu einer direkten Neuberechnung des Ausgangs.

## Anwendungsszenarien

*   **Volumenberechnungen:** Berechnung des Volumens aus drei Dimensionen (Länge $\times$ Breite $\times$ Höhe).
*   **Dreiphasen-Messungen:** Leistungs- oder Energieberechnungen, bei denen mehrere Faktoren (z. B. Strom, Spannung und ein Skalierungs-/Korrekturfaktor) miteinander multipliziert werden müssen.
*   **Mehrstufige Skalierung:** Einlesen eines Sensorwerts, der mit einem Kalibrierungswert und einem zusätzlichen Verstärkungsfaktor multipliziert werden muss.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu klassischen IEC 61131-3 `MUL`-Bausteinen bietet der `ADI_MUL_3` durch die Verwendung von Adaptern den Vorteil, dass Ereignisse und Daten logisch in einer einzigen Verbindung gekapselt sind. Dies reduziert den Verdrahtungsaufwand in der 4diac-IDE erheblich. Im Vergleich zu einem zweifachen Multiplizierer (`ADI_MUL_2`) spart dieser Baustein zudem ein Kaskadieren von Blöcken ein, was die Ausführungszeit verkürzt und das Anwendungsdiagramm übersichtlicher gestaltet.

## Fazit

Der `ADI_MUL_3` ist ein praktischer Hilfsbaustein für arithmetische Berechnungen in IEC 61499-Anwendungen. Durch die konsequente Nutzung von unidirektionalen Adaptern trägt er zu einem sauberen, lesbaren und wartungsfreundlichen Steuerungsentwurf bei.