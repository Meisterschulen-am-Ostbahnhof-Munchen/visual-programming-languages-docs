# GET_USINT


![GET_USINT](./GET_USINT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `GET_USINT` dient dem Auslesen eines `USINT`-Wertes aus einer InOut-Variable. Er puffert den gelesenen Wert und stellt ihn über einen Ausgang zur Verfügung. Der Baustein eignet sich insbesondere dann, wenn der Wert einer Variablen aus einem übergeordneten Kontext (z. B. einem Verbund) einmalig abgefragt und im weiteren Ablauf als konstanter Zwischenwert verwendet werden soll.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| REQ | Event | Normaler Ausführungsauftrag. Auslöser, um den aktuellen Wert von `IN` zu lesen und an `OUT` weiterzugeben. |

### **Ereignis-Ausgänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| CNF | Event | Bestätigung der erfolgreichen Ausführung. Wird nach dem Lesen und Puffern gesendet. |

### **Daten-Eingänge**

Der Baustein besitzt keine klassischen reinen Daten-Eingänge. Stattdessen wird der zu lesende Wert über die InOut-Variable `IN` bereitgestellt.

| Variable | Datentyp | Kommentar |
|----------|----------|-----------|
| IN | USINT | Quellvariable (InOut). Der aktuelle Wert dieser Variablen wird bei einem `REQ`-Ereignis gelesen und zwischengespeichert. Die Variable kann sowohl von außen beschrieben als auch ausgelesen werden; innerhalb des Bausteins erfolgt ausschließlich ein lesender Zugriff. |

### **Daten-Ausgänge**

| Variable | Datentyp | Kommentar |
|----------|----------|-----------|
| OUT | USINT | Gepufferter Ausgangswert. Enthält den bei der letzten Ausführung von `IN` gelesenen Wert. Initialwert: 0. |

### **Adapter**

Keine.

## Funktionsweise

1. Der Baustein wartet auf ein `REQ`-Ereignis.
2. Beim Eintreffen von `REQ` wird der aktuelle Wert der InOut-Variable `IN` gelesen und in die lokale Ausgangsvariable `OUT` kopiert (`OUT := IN;`).
3. Anschließend wird das Bestätigungsereignis `CNF` gesendet.
4. Der Wert von `OUT` bleibt so lange erhalten, bis ein weiteres `REQ`-Ereignis einen neuen Lesevorgang auslöst.

Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Verzweigungen oder zeitgesteuerten Abläufe – die Aktion wird in einem Schritt ausgeführt.

## Technische Besonderheiten

- **InOut-Variable `IN`** – Die Schnittstelle verwendet eine `InOut`-Variable, die sowohl als Eingang als auch als Ausgang fungiert. Dies ist typisch für 4diac-Funktionsblöcke, die auf Variablen eines übergeordneten Verbunds zugreifen. Der Baustein ändert den Wert von `IN` **nicht**, er liest ihn lediglich.
- **Pufferung** – Ohne erneutes `REQ` bleibt der Ausgangswert stabil, selbst wenn sich die Quellvariable später ändert. Dies entkoppelt den Wert vom Zeitpunkt des Lesens.
- **Keine Zustandsautomaten** – Der Baustein besteht aus nur einem Zustand `REQ`, was die Implementierung trivial und ressourcenschonend macht.

## Zustandsübersicht

Der Baustein besitzt genau einen Zustand:

| Zustand | Aktion | Ausgangsereignis |
|---------|--------|------------------|
| REQ | Führe Algorithmus `REQ` aus (`OUT := IN;`) | CNF |

Ein Startzustand ist nicht explizit definiert; nach dem Initialisieren wird der Baustein durch das erste `REQ` aktiv.

## Anwendungsszenarien

- **Einmaliges Abfragen einer Konfigurationsvariablen** – Ein in einer übergeordneten Ressource definierter `USINT`-Wert soll genau einmal zu Beginn des Ablaufs gelesen und danach als lokale Konstante verwendet werden.
- **Entkopplung von lesendem und schreibendem Zugriff** – Wenn eine Variable sowohl von mehreren Bausteinen geschrieben als auch gelesen wird, verhindert `GET_USINT` eine ständige Aktualisierung der lesenden Seite, da nur auf Anforderung gepuffert wird.
- **Testhilfsmittel** – Der Baustein kann genutzt werden, um den aktuellen Wert einer InOut-Variable in einem Diagnosezweig sichtbar zu machen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Typ | Besonderheit |
|----------|-----|--------------|
| `GET_USINT` | Eigener FB | Liest eine InOut-Variable und puffert den Wert. Ausgang bleibt stabil bis zum nächsten REQ. |
| `USINT_TO_*` (z. B. Konvertierer) | Konvertierungs-FB | Wandelt einen USINT in einen anderen Typ um, liest aber nicht zwingend aus einem InOut. |
| Direkter Datenzugriff | Kein FB | Ein Wert kann über Datenverbindungen ohne Puffer gelesen werden, jedoch ohne Entkopplung und ohne Ereignissteuerung. |

`GET_USINT` ist spezialisiert auf den lesenden Zugriff auf InOut-Variablen mit expliziter Pufferung und Ereignissteuerung – eine Aufgabe, die mit Standard-Konvertern oder direkten Verbindungen so nicht abgebildet werden kann.

## Fazit

Der `GET_USINT`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, einen `USINT`-Wert aus einer InOut-Variable auszulesen und als gepufferten Ausgang bereitzustellen. Seine klare, ereignisgesteuerte Schnittstelle und der minimale Zustandsautomat machen ihn zu einem nützlichen Werkzeug für Entkopplungs- und Initialisierungsaufgaben in 4diac-Anwendungen. Er ist ideal geeignet, wenn der Wert einer Variablen nur auf Anforderung abgerufen werden soll und zwischenzeitliche Änderungen der Quelle ignoriert werden müssen.