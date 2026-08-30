# CLIENT_8

![CLIENT_8](CLIENT_8.svg)

* * * * * * * * * *

## Einleitung

Der `CLIENT_8`-Funktionsblock ist die generische Client-Variante mit 8 Sende- und 8 Empfangsdatenfeldern für die Kommunikation mit einem passenden [SERVER_8](SERVER_8.md)-Block. Er überträgt 8 Datenwerte (`SD_1` `SD_2` `SD_3` `SD_4` `SD_5` `SD_6` `SD_7` `SD_8`) an den Server und empfängt 8 Datenwerte (`RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6` `RD_7` `RD_8`) zurück. Wie alle `CLIENT_*`-Bausteine basiert er auf der generischen `GEN_CLIENT`-Implementierung — dieselbe C++-Basis wie [CLIENT_1](CLIENT_1.md)/[SERVER_1](SERVER_1.md), lediglich die Anzahl der Sende-/Empfangsfelder unterscheidet sich pro Instanziierung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Öffnet eine neue Verbindung (QI = TRUE) oder schließt eine bestehende Verbindung (QI = FALSE), trägt `QI` und `ID`.
- **REQ**: Sendet Daten an den Server und fordert Daten vom Server an, trägt `QI` sowie `SD_1` `SD_2` `SD_3` `SD_4` `SD_5` `SD_6` `SD_7` `SD_8`.

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt Verbindungsauf-/-abbau, trägt `QO` und `STATUS`.
- **CNF**: Signalisiert, dass neue Daten vom Server verfügbar sind, trägt `QO`, `STATUS` sowie `RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6` `RD_7` `RD_8`.

### **Daten-Eingänge**

- **QI** (BOOL): Steuert den Verbindungsstatus (`TRUE` = Verbindung öffnen, `FALSE` = Verbindung schließen).
- **ID** (WSTRING): Identifikator der Verbindung (z. B. Zieladresse/Port).
- **SD_1** (ANY): Sendedatum 1, wird mit `REQ` an den Server übertragen.
- **SD_2** (ANY): Sendedatum 2, wird mit `REQ` an den Server übertragen.
- **SD_3** (ANY): Sendedatum 3, wird mit `REQ` an den Server übertragen.
- **SD_4** (ANY): Sendedatum 4, wird mit `REQ` an den Server übertragen.
- **SD_5** (ANY): Sendedatum 5, wird mit `REQ` an den Server übertragen.
- **SD_6** (ANY): Sendedatum 6, wird mit `REQ` an den Server übertragen.
- **SD_7** (ANY): Sendedatum 7, wird mit `REQ` an den Server übertragen.
- **SD_8** (ANY): Sendedatum 8, wird mit `REQ` an den Server übertragen.

### **Daten-Ausgänge**

- **QO** (BOOL): Aktueller Verbindungsstatus.
- **STATUS** (WSTRING): Statusinformationen zur Verbindung.
- **RD_1** (ANY): Empfangsdatum 1, wird mit `CNF` vom Server geliefert.
- **RD_2** (ANY): Empfangsdatum 2, wird mit `CNF` vom Server geliefert.
- **RD_3** (ANY): Empfangsdatum 3, wird mit `CNF` vom Server geliefert.
- **RD_4** (ANY): Empfangsdatum 4, wird mit `CNF` vom Server geliefert.
- **RD_5** (ANY): Empfangsdatum 5, wird mit `CNF` vom Server geliefert.
- **RD_6** (ANY): Empfangsdatum 6, wird mit `CNF` vom Server geliefert.
- **RD_7** (ANY): Empfangsdatum 7, wird mit `CNF` vom Server geliefert.
- **RD_8** (ANY): Empfangsdatum 8, wird mit `CNF` vom Server geliefert.

## Funktionsweise

`CLIENT_8` initialisiert über `INIT` eine Verbindung zum passenden `SERVER_8`-Block (bei `QI = TRUE`) bzw. schließt sie (bei `QI = FALSE`); der Abschluss wird über `INITO` bestätigt. Über `REQ` werden `SD_1` `SD_2` `SD_3` `SD_4` `SD_5` `SD_6` `SD_7` `SD_8` an den Server übertragen. Sobald Antwortdaten (`RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6` `RD_7` `RD_8`) vorliegen, löst der Baustein `CNF` aus und stellt `RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6` `RD_7` `RD_8` bereit.

## Technische Besonderheiten

- **Generische Implementierung**: `eclipse4diac::core::GenericClassName = 'GEN_CLIENT'`, dieselbe C++-Basis wie alle anderen `CLIENT_*`-Varianten; Anzahl und Typ (`ANY`) der Sende-/Empfangsfelder werden pro Instanziierung über die Typdefinition festgelegt.
- **`ANY`-Datenfelder**: Alle `SD_i`/`RD_i` sind generisch (`ANY`) typisiert und passen sich beim Verdrahten an den jeweils angeschlossenen Datentyp an.
- **Gegenstück `SERVER_8`**: `CLIENT_8` ist funktional nur mit einem `SERVER_8`-Block auf der Server-Seite kompatibel — die Anzahl der Sendefelder der einen Seite muss der Anzahl der Empfangsfelder der Gegenseite entsprechen.

## Zustandsübersicht

1. **Nicht verbunden**: Initialzustand, `QO = FALSE`.
2. **Verbindungsaufbau**: `INIT` mit `QI = TRUE` wird verarbeitet.
3. **Verbunden**: `INITO` mit `QO = TRUE` bestätigt die Verbindung.
4. **Datenaustausch**: `REQ`/`CNF`-Zyklus für Sende-/Empfangsdaten.
5. **Verbindungstrennung**: `INIT` mit `QI = FALSE` wird verarbeitet.

## Anwendungsszenarien

- **Kommunikation zwischen verteilten Steuerungssystemen**, bei denen genau 8 Werte gesendet und 8 Werte empfangen werden sollen, ohne überzählige, ungenutzte Datenfelder in Kauf zu nehmen.
- **Client-seitige Anbindung** eines Kommunikationspartners, der bereits als `SERVER_8` mit passender Feldanzahl ausgelegt ist.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[SERVER_8](SERVER_8.md)**: das direkte Gegenstück auf der Server-Seite, mit vertauschter Sende-/Empfangsfeldanzahl.
- **[CLIENT_1](CLIENT_1.md) / [SERVER_1](SERVER_1.md)**: dieselbe generische Implementierung mit je einem Sende- und Empfangsfeld.

## Fazit

`CLIENT_8` liefert die generische, auf 8 Sende- und 8 Empfangsfelder zugeschnittene Client-Variante der `GEN_CLIENT`-Familie und eignet sich für Netzwerkverbindungen, deren Nutzdatenanzahl von der Standardvariante mit einem Feld abweicht.
