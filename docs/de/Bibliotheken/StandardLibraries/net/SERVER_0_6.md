# SERVER_0_6

![SERVER_0_6](SERVER_0_6.svg)

* * * * * * * * * *
## Einleitung

Der `SERVER_0_6`-Funktionsblock ist die generische Server-Variante mit 0 Sende- und 6 Empfangsdatenfeldern für die Kommunikation mit einem passenden [CLIENT_6_0](CLIENT_6_0.md)-Block. Er empfängt 6 Datenwerte (`RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6`) vom Client, ohne selbst Nutzdaten zu senden. Wie alle `SERVER_*`-Bausteine basiert er auf der generischen `GEN_SERVER`-Implementierung — dieselbe C++-Basis wie [CLIENT_1](CLIENT_1.md)/[SERVER_1](SERVER_1.md), lediglich die Anzahl der Sende-/Empfangsfelder unterscheidet sich pro Instanziierung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Aktiviert den Server für eine Client-Verbindung (QI = TRUE) bzw. schließt ihn (QI = FALSE), trägt `QI` und `ID`.
- **RSP**: Sendet Daten an den Client, trägt `QI`.

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt Verbindungsauf-/-abbau, trägt `QO` und `STATUS`.
- **IND**: Signalisiert, dass neue Daten vom Client verfügbar sind, trägt `QO`, `STATUS` sowie `RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6`.

### **Daten-Eingänge**

- **QI** (BOOL): Steuert den Verbindungsstatus (`TRUE` = Verbindung öffnen, `FALSE` = Verbindung schließen).
- **ID** (WSTRING): Identifikator der Verbindung (z. B. Zieladresse/Port).
- Keine Sendedaten (`SERVER_0_6` überträgt keine Nutzdaten mit `RSP`, nur die Verbindungssteuerung).

### **Daten-Ausgänge**

- **QO** (BOOL): Aktueller Verbindungsstatus.
- **STATUS** (WSTRING): Statusinformationen zur Verbindung.
- **RD_1** (ANY): Empfangsdatum 1, wird mit `IND` vom Client geliefert.
- **RD_2** (ANY): Empfangsdatum 2, wird mit `IND` vom Client geliefert.
- **RD_3** (ANY): Empfangsdatum 3, wird mit `IND` vom Client geliefert.
- **RD_4** (ANY): Empfangsdatum 4, wird mit `IND` vom Client geliefert.
- **RD_5** (ANY): Empfangsdatum 5, wird mit `IND` vom Client geliefert.
- **RD_6** (ANY): Empfangsdatum 6, wird mit `IND` vom Client geliefert.

## Funktionsweise

`SERVER_0_6` initialisiert über `INIT` eine Verbindung zum passenden `CLIENT_6_0`-Block (bei `QI = TRUE`) bzw. schließt sie (bei `QI = FALSE`); der Abschluss wird über `INITO` bestätigt. Über `RSP` wird eine Anfrage ohne Nutzdaten gesendet. Sobald Antwortdaten (`RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6`) vorliegen, löst der Baustein `IND` aus und stellt `RD_1` `RD_2` `RD_3` `RD_4` `RD_5` `RD_6` bereit.

## Technische Besonderheiten

- **Generische Implementierung**: `eclipse4diac::core::GenericClassName = 'GEN_SERVER'`, dieselbe C++-Basis wie alle anderen `SERVER_*`-Varianten; Anzahl und Typ (`ANY`) der Sende-/Empfangsfelder werden pro Instanziierung über die Typdefinition festgelegt.
- **`ANY`-Datenfelder**: Alle `SD_i`/`RD_i` sind generisch (`ANY`) typisiert und passen sich beim Verdrahten an den jeweils angeschlossenen Datentyp an.
- **Gegenstück `CLIENT_6_0`**: `SERVER_0_6` ist funktional nur mit einem `CLIENT_6_0`-Block auf der Client-Seite kompatibel — die Anzahl der Sendefelder der einen Seite muss der Anzahl der Empfangsfelder der Gegenseite entsprechen.

## Zustandsübersicht

1. **Nicht verbunden**: Initialzustand, `QO = FALSE`.
2. **Verbindungsaufbau**: `INIT` mit `QI = TRUE` wird verarbeitet.
3. **Verbunden**: `INITO` mit `QO = TRUE` bestätigt die Verbindung.
4. **Datenaustausch**: `RSP`/`IND`-Zyklus für Sende-/Empfangsdaten.
5. **Verbindungstrennung**: `INIT` mit `QI = FALSE` wird verarbeitet.

## Anwendungsszenarien

- **Kommunikation zwischen verteilten Steuerungssystemen**, bei denen genau 0 Werte gesendet und 6 Werte empfangen werden sollen, ohne überzählige, ungenutzte Datenfelder in Kauf zu nehmen.
- **Server-seitige Anbindung** eines Kommunikationspartners, der bereits als `CLIENT_6_0` mit passender Feldanzahl ausgelegt ist.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[CLIENT_6_0](CLIENT_6_0.md)**: das direkte Gegenstück auf der Client-Seite, mit vertauschter Sende-/Empfangsfeldanzahl.
- **[CLIENT_1](CLIENT_1.md) / [SERVER_1](SERVER_1.md)**: dieselbe generische Implementierung mit je einem Sende- und Empfangsfeld.

## Fazit

`SERVER_0_6` liefert die generische, auf 0 Sende- und 6 Empfangsfelder zugeschnittene Server-Variante der `GEN_SERVER`-Familie und eignet sich für Netzwerkverbindungen, deren Nutzdatenanzahl von der Standardvariante mit einem Feld abweicht.
