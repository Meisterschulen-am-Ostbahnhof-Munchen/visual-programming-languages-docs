# AI_TO_ALR


![AI_TO_ALR](./AI_TO_ALR.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AI_TO_ALR** ist ein Composite-Baustein, der einen **AI (Adapter INT)** in einen **ALR (Adapter LREAL)** umwandelt. Er dient als reine Konvertierungsschnittstelle, indem er die Ereignis- und Datenkanäle des Eingangsadapters direkt auf den Ausgangsadapter durchschleift. Die eigentliche Typkonvertierung von Integer (INT) nach Long Real (LREAL) wird von den zugrunde liegenden Adapterdefinitionen übernommen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der Baustein besitzt keine direkten Ereignis-Eingänge. Das Ereignis wird über den Socket‑Adapter `AI_IN` empfangen:
- **AI_IN.E1** – Ereignis des INT-Adapters (Eingang).

### **Ereignis-Ausgänge**
Auch hier gibt es keine direkten Ereignis-Ausgänge. Das Ereignis wird über den Plug‑Adapter `ALR_OUT` gesendet:
- **ALR_OUT.E1** – Ereignis des LREAL-Adapters (Ausgang).

### **Daten-Eingänge**
- **AI_IN.D1** – Datenwert vom Typ INT (über den Adapter).

### **Daten-Ausgänge**
- **ALR_OUT.D1** – Datenwert vom Typ LREAL (über den Adapter).

### **Adapter**
- **AI_IN** (Socket) – Adapter vom Typ `AI` (INT‑Adapter), Eingangsschnittstelle.
- **ALR_OUT** (Plug) – Adapter vom Typ `ALR` (LREAL‑Adapter), Ausgangsschnittstelle.

## Funktionsweise

Der Baustein verbindet die Signale des Socket‑Adapters `AI_IN` direkt mit dem Plug‑Adapter `ALR_OUT`:

- **Ereignispfad:** Das an `AI_IN.E1` eingehende Ereignis wird unverändert an `ALR_OUT.E1` weitergeleitet.
- **Datenpfad:** Der an `AI_IN.D1` anliegende INT‑Wert wird an `ALR_OUT.D1` übergeben. Die Adapter selbst implementieren die notwendige Typkonvertierung von INT nach LREAL.

Da es sich um einen Composite‑Baustein ohne eigenen Algorithmus oder Zustandsautomaten handelt, erfolgt keine weitere Verarbeitung. Der Baustein fungiert als reine Routing‑ und Anpassungsschicht zwischen unterschiedlichen Adaptertypen.

## Technische Besonderheiten

- **Reine Durchleitstruktur:** Keine eigene Logik, keine Latenz oder Pufferung.
- **Abhängigkeit von Adapterdefinitionen:** Die korrekte Funktion setzt voraus, dass die Adapter `AI` und `ALR` gemäß dem 4diac‑Standard definiert sind und die Konvertierung INT‑>LREAL enthalten.
- **Komposit‑Baustein:** Einfach erweiterbar, z. B. durch zusätzliche Filter oder Skalierung im Netzwerk.
- **Paketstruktur:** Der Baustein liegt im Paket `adapter::conversion::unidirectional`.

## Zustandsübersicht

Der Baustein besitzt kein eigenes Zustandsdiagramm (ECC). Die Signalverarbeitung erfolgt rein ereignisgesteuert über die durchgeschliffenen Adapter‑Ereignisse. Ein Zustand ist daher nicht definiert.

## Anwendungsszenarien

- **Systemintegration:** Verbindung eines INT‑basierten Sensors (z. B. Digitalwert aus Zähler) mit einer Komponente, die LREAL‑Werte erwartet (z. B. Regelalgorithmus).
- **Adapter‑Brücke:** Einsatz in modularen Automatisierungssystemen, bei denen unterschiedliche Adaptertypen aufeinandertreffen.
- **Prototypenentwicklung:** Schnelle Kopplung von Test‑Bausteinen unterschiedlicher Datenformate.

## Vergleich mit ähnlichen Bausteinen

Während es in 4diac‑Bibliotheken oft separate Konverter‑Bausteine für Basisdatentypen gibt (z. B. `INT_TO_REAL`), kapselt `AI_TO_ALR` die Konvertierung auf Adapterebene. Der Vorteil liegt in der Wiederverwendbarkeit von Adapterschnittstellen und der einfachen Austauschbarkeit der Konvertierungslogik durch andere Adapter. Nachteil ist die Abhängigkeit von den konkreten Adapterdefinitionen.

## Fazit

Der Baustein **AI_TO_ALR** ist ein minimalistischer, aber effektiver Composite‑FB zur Typanpassung zwischen INT‑ und LREAL‑Adapter. Er reduziert den Verdrahtungsaufwand in komplexen Steuerungsnetzwerken und ermöglicht eine saubere Trennung von Schnittstellen und Konvertierungslogik. Für Anwendungen, die eine reine Durchleitung ohne zusätzliche Verarbeitung benötigen, stellt er eine ideale Lösung dar.