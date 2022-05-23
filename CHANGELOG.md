# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.0.0.1005] - 2022-05-23

### Added

- Added arguments and fields to `Transaction.gql` template file for getting the wallet address.
- Added arguments and fields to `Wallet.gql` template file for getting balances and transactions.
- Added `set_with_transaction_wallet_address` member-function to `TransactionFragmentArguments`.
- Added `set_wallet_balance_filter`, `set_with_wallet_balances`, and `set_with_wallet_transaction` member-functions
  to `WalletFragmentArguments`.
- Added getters for balances and transactions to `Wallet` model.

### Changed

- Refactored `Balance`, `Player`, `Request`, and `Wallet` models to use pimpl idiom.
- Changed name of member-function `set_asset_id_format` in `TransactionFragmentArguments`
  to `set_transaction_asset_id_format`.
- `WalletFragmentArguments` now implements `BalanceFragmentArguments` and `TransactionFragmentArguments`.

### Fixed

- Fixed issue with argument interfaces not serializing data from parent argument interfaces.
- Fixed missing equality operator in `ProjectTransactionRequestArguments`.

## [1.0.0.1004] - 2022-04-25

### Changed

- Removed `set_project_uuid` and `set_project_uuid_in` member-functions from `BalanceFilter`.

## [1.0.0.1003] - 2022-04-11

### Changed

- `GetWallets` query in project schema no longer implements `PaginationArguments`.

### Fixed

- Fixed typo for `result` in `GetWallets.gql` template file for project schema.

## [1.0.0.1002] - 2022-03-01

### Changed

- Updated path to template generation command in root CMakeLists file.
- Updated regular expression used by `TemplateLoader` to match a wider range of characters leading to the "schemas"
  folder.

### Fixed

- Fixed package installation procedure in root CMakeLists file.

## [1.0.0.1001] - 2021-11-09

### Added

- Added [Enjin Bridge mutations](https://docs.enjin.io/enjin-api/sending-and-receiving-requests/enjin-bridge) for
  project and player schemas.
- Added `get_asset` member-function to `Request`.
- Added `set_asset_id_format` method to `TransactionFragmentArguments`.

### Changed

- The asset for transactions is now included in returned `Request` models when using `set_with_asset_data()` in requests
  which inherit `TransactionFragmentArguments`.

## [1.0.0.1000] - 2021-09-27

### Added

- Initial alpha release.

[Unreleased]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.1005...HEAD

[1.0.0.1005]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.1004...1.0.0.1005

[1.0.0.1004]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.1003...1.0.0.1004

[1.0.0.1003]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.1002...1.0.0.1003

[1.0.0.1002]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.1001...1.0.0.1002

[1.0.0.1001]: https://github.com/enjin/enjin-cpp-sdk/compare/1.0.0.1000...1.0.0.1001

[1.0.0.1000]: https://github.com/enjin/enjin-cpp-sdk/releases/tag/1.0.0.1000