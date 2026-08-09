# Exercise_012c: Numeric Value Input and Storage via INI with Subapp

[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)
This article describes the logiBUS® exercise `Uebung_012c`. It demonstrates that text information can also be stored persistently.
----
## Objective of the Exercise

Handling the data type `STRING` during storage.

-----

## Description and Components

[cite_start]In `Uebung_012c.SUB`, a string value is managed via an INI block[cite: 1].

### Function Blocks (FBs)

* **`INI`**: Configured here for the data type `STRING`.
* **`Q_StringValue`**: An ISOBUS output module specifically designed for displaying text (instead of numbers).

-----

## Functionality

The process is identical to numerical storage, however, character strings now flow over the data connections. At system startup, the stored text (e.g., a device name or user profile) is loaded and sent to the terminal.

-----

## Application Example

**Personalization**:

The user can enter their name or the name of the field they are currently working on at the terminal. This information is permanently stored and can later be used for logging purposes (e.g., task controllers).